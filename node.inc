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

class OlinUrisBlogMigration extends OlinUrisNodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_blog_link', 'field_blink')
         ->description('Blog Link Field');
    $this->addFieldMapping('field_blog_link:title', 'field_blink:title')
         ->description('Blog Link Title Field');

    $this->addFieldMapping('body:format', NULL, FALSE)
        ->defaultValue('full_html');
  }
}

class OlinUrisCourseGuideMigration extends OlinUrisNodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_course_guide_link', 'field_guide_link')
         ->description('Course Guide Link Field');
    $this->addFieldMapping('field_course_guide_link:title', 'field_guide_link:title')
         ->description('Course Guide Link Title Field');

    $this->addFieldMapping('body:format', NULL, FALSE)
        ->defaultValue('full_html');
  }
}

class OlinUrisSignMigration extends OlinUrisNodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_sign_image', 'field_image')
         ->description('Digital Sign Field')
         ->sourceMigration('File');
    $this->addFieldMapping('field_sign_image:file_class')
         ->defaultValue('MigrateFileFid');

    $this->addFieldMapping('field_sign_visible_during', 'date_range')
         ->description('Digital Sign Sunrise Field');

    $this->addFieldMapping('field_sign_image_link', 'field_imagelink')
         ->description('Digital Sign Link Field');
    $this->addFieldMapping('field_sign_image_link:title', 'field_imagelink:title')
         ->description('Digital Sign Link Title Field');

    $this->addFieldMapping('body:format', NULL, FALSE)
        ->defaultValue('full_html');
  }
  public function prepareRow($current_row) {
    // The date range field can have multiple values.
    $current_row->date_range = array();
    // static $jgr_first = TRUE;
    // if ($jgr_first) {
    //   $jgr_first = FALSE;
    //   dsm($current_row);
    // }
    $date_range = array(
      'from' => $current_row->field_sunrise,
      'to' => $current_row->field_sunrise_value2,
    );
    $current_row->date_range = drupal_json_encode($date_range);
  }
}


class OlinUrisEquipmentMigration extends OlinUrisNodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_equipment_id', 'field_equip_id')
         ->description('Equipment ID Field');
    $this->addFieldMapping('field_equipment_name', 'field_equip_name')
         ->description('Equipment Name Field');
   $this->addFieldMapping('field_equipment_description', 'field_equip_desc')
         ->description('Equipment Description Field');
   $this->addFieldMapping('field_equipment_type', 'field_equip_type')
         ->description('Equipment Type Field');
   $this->addFieldMapping('field_equipment_item_id', 'field_equip_item_id')
         ->description('Equipment Item ID Field');
   $this->addFieldMapping('field_equipment_bibid', 'field_equip_bibid')
         ->description('Equipment BibID Field');
   $this->addFieldMapping('field_equipment_date_due', 'field_equip_date_due')
         ->description('Equipment Date Due Field');
   $this->addFieldMapping('field_equipment_loan_period', 'field_equip_loan_period')
         ->description('Equipment Loan Period');
   $this->addFieldMapping('field_equipment_reservable', 'field_equip_reservable')
         ->description('Equipment Reservable Field');
   $this->addFieldMapping('field_equipment_available', 'field_equip_available')
         ->description('Equipment Available Field');

    $this->addFieldMapping('body:format', NULL, FALSE)
        ->defaultValue('full_html');
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
