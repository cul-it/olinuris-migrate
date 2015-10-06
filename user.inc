<?php

/**
 * Common mappings for the Drupal 6 user migrations.
 */
abstract class OlinUrisUserMigration extends DrupalUser6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

  $this->addFieldMapping('roles', 'roles')
    ->sourceMigration('role_migration_machine_name');
  }
}
