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
    'source_version' => 6,
    'group_name' => 'content_migration',
    'source_connection' => 'legacy',
    'source_database' => array(
      'driver' => 'mysql',
      'database' => 'olinuris6',
      'username' => 'drupaluser', // Ideally this user has readonly access
      // Best practice: use a variable (defined by setting $conf in settings.php, or
      // with drush vset) for the password rather than exposing it in the code.
      'password' => variable_get('olinuris_migrate_password', ''),
      'host' => '127.0.0.1',
      'port' => '33067',
      'prefix' => '',
    ),
    'format_mappings' => array(
      '1' => 'filtered_html',
      '2' => 'full_html',
      '4' => 'secure_filtered_html',
      '5' => 'unfiltered',
    ),
  );

  // register role migration
  $role_arguments = $common_arguments + array(
    'machine_name' => 'olinuris_role',
    'description' => t('Import Drupal 6 roles'),
    'role_mappings' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'Digital Sign Worker' => 'Digital Sign Worker',
      'Form Editor' => 'Form Editor',
      'unfiltered contributor' => 'unfiltered contributor',
      ),
    );
   Migration::registerMigration('DrupalRole6Migration',
    $role_arguments['machine_name'], $role_arguments);

  $user_arguments = $common_arguments + array(
    'description' => t('Migration of users from Drupal 6'),
    'machine_name' => 'olinuris_user',
    'class_name' => 'OlinUrisUserMigration',
    'role_migration' => 'olinuris_role',
    );
  Migration::registerMigration('DrupalUser6Migration', $user_arguments['machine_name'], $user_arguments);


  // For vocabulary migrations, source_vocabulary and destination_vocabulary are
  // required arguments. Note that in Drupal 6 vocabularies did not have machine
  // names, so we use the vocabulary ID to uniquely identify them.
  $vocabulary_arguments = array(
    'olinuris_vocab_localist_event_type' => array(
      'description' => t('Migration of Localist Event Types terms from Drupal 6'),
      'source_vocabulary' => '14',  // D6 Vocabulary ID
      'destination_vocabulary' => 'localist_event_type',
    ),
    'olinuris_vocab_service_hours' => array(
      'description' => t('Migration of Hours Building or Service terms from Drupal 6'),
      'source_vocabulary' => '9',  // D6 Vocabulary ID
      'destination_vocabulary' => 'service_hours',
    ),
    'olinuris_vocab_import_tags' => array(
      'description' => t('Migration of Import Tags terms from Drupal 6'),
      'source_vocabulary' => '2',  // D6 Vocabulary ID
      'destination_vocabulary' => 'import_tags',
    ),
    'olinuris_vocab_sections' => array(
      'description' => t('Migration of Sections terms from Drupal 6'),
      'source_vocabulary' => '5',  // D6 Vocabulary ID
      'destination_vocabulary' => 'sections',
    ),
    'olinuris_vocab_subject_guide_type' => array(
      'description' => t('Migration of Subject Guide Type terms from Drupal 6'),
      'source_vocabulary' => '10',  // D6 Vocabulary ID
      'destination_vocabulary' => 'subject_guide_type',
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
    'Blog' => array(
      'class_name' => 'OlinUrisBlogMigration',
      'description' => t('Migration of Blog nodes from Drupal 6'),
      'source_type' => 'blog_entry',
      'destination_type' => 'blog_entry',
    ),
    'Course_Guide_Link' => array(
      'class_name' => 'OlinUrisCourseGuideMigration',
      'description' => t('Migration of Course Guide Link nodes from Drupal 6'),
      'source_type' => 'course_guide_link',
      'destination_type' => 'course_guide_link',
    ),
    'Digital_Sign' => array(
      'class_name' => 'OlinUrisSignMigration',
      'description' => t('Migration of Digital Sign nodes from Drupal 6'),
      'source_type' => 'digital_sign',
      'destination_type' => 'digital_sign',
    ),
    'Equipment' => array(
      'class_name' => 'OlinUrisEquipmentMigration',
      'description' => t('Migration of Equipment nodes from Drupal 6'),
      'source_type' => 'equipment',
      'destination_type' => 'equipment',
    ),
    // 'Article' => array(
    //   'class_name' => 'OlinUrisArticleMigration',
    //   'description' => t('Migration of article nodes from Drupal 6'),
    //   'source_type' => 'my_article',
    //   'destination_type' => 'new_article',
    //   'dependencies' => array('Image', 'Countries', 'Topics'),
    // ),
  );

  // Register the file migration.
  // source_dir needs to be adjusted to match your file system.
  $api['migrations']['File'] = $common_arguments + array(
    'machine_name' => 'filemigration',
    'description' => t('Import Drupal 6 files'),
    'class_name' => 'FileMigration',
    'user_migration' => 'olinuris_user',
    'default_uid' => 1,
    'source_dir' => '/Users/jgr25/Sites/devdesktop/olinuris6',
    'destination_dir' => 'public://',
  );

  /**
   * Tell the node migrations where the users are coming from, so they can
   * set up the dependency and resolve D6->D7 uids.
   */
  $common_node_arguments = $common_arguments + array(
      'user_migration' => 'olinuris_user'
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
