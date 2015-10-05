<?php

/**
 * Common mappings for the Drupal 6 node migrations.
 */
abstract class OlinUrisNodeMigration extends DrupalNode6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_legacy_nid', 'nid')
         ->description('We have a common field to save the D6 nid');
  }
}


// class OlinUrisArticleMigration extends OlinUrisNodeMigration {
//   public function __construct(array $arguments) {
//     // Add any other data we're pulling into the source row, before the parent
//     // constructor.
//     $this->sourceFields['lead_graphic'] = 'Lead graphic string from D6';
//     $this->sourceFields['summary'] = 'Summary string from D6';

//     parent::__construct($arguments);

//     $this->addFieldMapping('field_image', 'field_lead_graphic')
//          ->sourceMigration('Image');
//     // Note that we map migrated terms by the vocabulary ID.
//     $this->addFieldMapping('field_countries', '1')
//          ->sourceMigration('Countries');
//     $this->addFieldMapping('field_countries:source_type')
//          ->defaultValue('tid');
//     $this->addFieldMapping('field_topics', '2')
//          ->sourceMigration('Topics');
//     $this->addFieldMapping('field_topics:source_type')
//          ->defaultValue('tid');
//   }
// }
