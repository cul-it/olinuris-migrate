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

    $this->addFieldMapping('field_sign_visible_during', 'field_sunrise')
         ->description('Digital Sign Sunrise Field');
    $this->addFieldMapping('field_sign_image_link', 'field_imagelink')
         ->description('Digital Sign Link Field');
    $this->addFieldMapping('field_sign_image_link:title', 'field_imagelink:title')
         ->description('Digital Sign Link Title Field');

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
