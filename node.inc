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


class OlinUrisBannerImageMigration extends OlinUrisNodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_banner_image_photo', 'field_bannerimg')
         ->description('Banner Image Photo Field')
         ->sourceMigration('File');
    $this->addFieldMapping('field_banner_image_photo:file_class')
         ->defaultValue('MigrateFileFid');

    $this->addFieldMapping('field_banner_image_sunrise', 'field_bannersunrise')
         ->description('Digital Sign Sunrise Field');
    $this->addFieldMapping('field_banner_image_sunset', 'field_bannersunset')
         ->description('Digital Sign SunsetField');

    $this->addFieldMapping('body:format', NULL, FALSE)
        ->defaultValue('full_html');

   }
}

class OlinUrisImportedPageMigration extends OlinUrisNodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_imported_page_section', 'field_section')
        ->description('Imported Page Section Field')
        ->sourceMigration('olinuris_vocab_sections');
    $this->addFieldMapping('field_imported_page_section:source_type')
        ->defaultValue('tid');

    $this->addFieldMapping('field_imported_page_contact', 'field_page_contact')
         ->description('Imported Page Contact Field')
         ->defaultValue('1');

    $this->addFieldMapping('body:format', NULL, FALSE)
        ->defaultValue('full_html');

   }
  // public function prepareRow($current_row) {
  //   static $jgr_first = TRUE;
  //   if ($jgr_first) {
  //     $jgr_first = FALSE;
  //     dsm($current_row);
  //   }
  // }
}

class OlinUrisLaptopCountMigration extends OlinUrisNodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_laptop_count_pc', 'field_laptop_avail')
         ->description('Laptop Count PC Field');

    $this->addFieldMapping('field_laptop_count_mac', 'field_mac_laptop_avail')
         ->description('Laptop Count Mac Field');

    $this->addFieldMapping('field_laptop_count_library', 'field_library_name')
         ->description('Laptop Count Library Field');

    $this->addFieldMapping('body:format', NULL, FALSE)
        ->defaultValue('full_html');

   }
}
