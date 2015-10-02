<?php

/**
 * Image-specific mappings and handling.
 */
class PhotoMigration extends ExampleNodeMigration {
  public function __construct(array $arguments) {

    parent::__construct($arguments);

    $this->addFieldMapping('field_photocaption', 'field_photocaption');
    $this->addFieldMapping('field_photoimage', 'field_image')
      ->sourceMigration('File');
    $this->addFieldMapping('field_photoimage:file_class')
      ->defaultValue('MigrateFileFid');
    }

  /**
   * Implementation of Migration::prepareRow().
   *
   * Here we pull in additional data from a non-core, non-CCK table.
   *
   * @param $row
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
  }
}
