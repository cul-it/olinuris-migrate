<?php
/**
 * @file olinuris_migrate.migrate.inc
 */

/**
 * This is example code for a Drupal 6 to Drupal 7 migration. This won't actually
 * work without defining the referenced vocabularies, content types, and fields
 * on each side.
 */

/**
 * Implements hook_migrate_api().
 */
function olinuris_migrate_migrate_api() {
  /**
   * Declare the api version and migration group.
   */
  $api = array(
    'api' => 2,
    'groups' => array(
      'content_migration' => array(
        'title' => t('Drupal 6 to Drupal 7 Olin/Uris migrations.'),
      ),
      'migrations' => array(),
    ),
  );

  /**
   * Each migration being registered takes an array of arguments, some required
   * and some optional. Start with the common arguments required by all - the
   * source_connection (connection key, set up in settings.php, pointing to
   * the Drupal 6 database), source_version (major version of Drupal), and
   * group_name (a.k.a. import job).
   */
  $common_arguments = array(
    'source_connection' => 'legacy',
    'source_version' => 6,
    'group_name' => 'content_migration',
  );

  // Register the user migration.
  // We just use the migrate_d2d D6 migration class as-is.
  $api['migrations']['User'] = $common_arguments + array(
    'description' => t('Migration of users from Drupal 6'),
    'class_name' => 'DrupalUser6Migration',
  );

  // For vocabulary migrations, source_vocabulary and destination_vocabulary are
  // required arguments. Note that in Drupal 6 vocabularies did not have machine
  // names, so we use the vocabulary ID to uniquely identify them.
  $vocabulary_arguments = array(
    'Event Type' => array(
      'description' => t('Migration of Localist Event Types terms from Drupal 6'),
      'source_vocabulary' => '14',  // D6 Vocabulary ID
      'destination_vocabulary' => 'localist_event_type',
    ),
    'Service Hours' => array(
      'description' => t('Migration of Hours Building or Service terms from Drupal 6'),
      'source_vocabulary' => '9',  // D6 Vocabulary ID
      'destination_vocabulary' => 'service_hours',
    ),
    'Import Tags' => array(
      'description' => t('Migration of Import Tags terms from Drupal 6'),
      'source_vocabulary' => '2',  // D6 Vocabulary ID
      'destination_vocabulary' => 'import_tags',
    ),
    'Sections' => array(
      'description' => t('Migration of Sections terms from Drupal 6'),
      'source_vocabulary' => '5',  // D6 Vocabulary ID
      'destination_vocabulary' => 'sections',
    ),
    'Subject Guide Type' => array(
      'description' => t('Migration of Subject Guide Type terms from Drupal 6'),
      'source_vocabulary' => '10',  // D6 Vocabulary ID
      'destination_vocabulary' => 'service_hours',
    ),
  );

  // Again, we're using the migrate_d2d class directly.
  // The soft dependency says that while we don't have to run the user migration
  // first, we want to make sure it's listed first so the vocabularies are
  // listed right ahead of the node migrations.
  $common_vocabulary_arguments = $common_arguments + array(
    'class_name' => 'DrupalTerm6Migration',
    'soft_dependencies' => array('User'),
  );
  foreach ($vocabulary_arguments as $migration_name => $arguments) {
    $arguments += $common_vocabulary_arguments;
    $api['migrations'][$migration_name] = $arguments;
  }

  // Node migrations - each has its own class derived from the migrate_d2d class,
  // specifying its particular field mappings and transformations. source_type
  // and destination_type are required arguments.
  $node_arguments = array(
    'Photos' => array(
      'class_name' => 'PhotoMigration',
      'description' => t('Migration of photo nodes from Drupal 6'),
      'source_type' => 'photo',
      'destination_type' => 'photo',
    ),
    'Article' => array(
      'class_name' => 'OlinUrisArticleMigration',
      'description' => t('Migration of article nodes from Drupal 6'),
      'source_type' => 'my_article',
      'destination_type' => 'new_article',
      'dependencies' => array('Image', 'Countries', 'Topics'),
    ),
  );

  // Register the file migration.
  // source_dir needs to be adjusted to match your file system.
  $api['migrations']['File'] = $common_arguments + array(
    'machine_name' => 'filemigration',
    'description' => t('Import Drupal 6 files'),
    'class_name' => 'FileMigration',
    'user_migration' => 'User',
    'default_uid' => 1,
    'source_dir' => '/Users/jgr25/Sites/devdesktop/olinuris6',
    'destination_dir' => 'public://',
  );

  /**
   * Tell the node migrations where the users are coming from, so they can
   * set up the dependency and resolve D6->D7 uids.
   */
  $common_node_arguments = $common_arguments + array(
      'user_migration' => 'User'
    );

  foreach ($node_arguments as $migration_name => $arguments) {
    $arguments = array_merge_recursive($arguments, $common_node_arguments);
    $api['migrations'][$migration_name] = $arguments;
  }

  // Menu migrations -- same requirements as users
  $menu_arguments = $common_arguments + array(
    'description' => t('Migration of menus from Drupal 6'),
    'class_name' => 'DrupalMenu6Migration',
  );

  // We just use the migrate_d2d D6 migration class as-is.
  $api['migrations']['Menu'] = $menu_arguments;

  // Menu links migrations -- basic requirements, plus must set up menu dependency
  $menu_links_arguments = $common_arguments + array(
    'description' => t('Migration of menu links from Drupal 6'),
    'class_name' => 'DrupalMenuLinks6Migration',
    'menu_migration' => 'Menu',
  );
  $api['migrations']['MenuLinks'] = $menu_links_arguments;

  return $api;
}
