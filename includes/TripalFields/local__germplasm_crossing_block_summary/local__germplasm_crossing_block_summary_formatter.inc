<?php
/**
 * @class
 * Purpose: Provide a quick search on entity pages which submits/redirects to a full search.
 *
 * Display: A simple textfield search form.
 * Configuration:
 *   - path to the full search.
 *   - the URL token (query parameter) the value applies to.
 *   - help text.
 *   - textfield placeholder.
 *   - search button text.
 *   - autocomplete path.
 */
class local__germplasm_crossing_block_summary_formatter extends TripalFieldFormatter {
  // The default label for this field.
  public static $default_label = 'Germplasm Crossing Block Summary';

  // The list of field types for which this formatter is appropriate.
  public static $field_types = array('local__germplasm_crossing_block_summary');

  /**
   *  Provides the display for a field
   *
   * This function corresponds to the hook_field_formatter_view()
   * function of the Drupal Field API.
   *
   *  This function provides the display for a field when it is viewed on
   *  the web page.  The content returned by the formatter should only include
   *  what is present in the $items[$delta]['values] array. This way, the
   *  contents that are displayed on the page, via webservices and downloaded
   *  into a CSV file will always be identical.  The view need not show all
   *  of the data in the 'values' array.
   *
   *  @param $element
   *  @param $entity_type
   *  @param $entity
   *  @param $langcode
   *  @param $items
   *  @param $display
   *
   *  @return
   *    An element array compatible with that returned by the
   *    hook_field_formatter_view() function.
   */
  public function view(&$element, $entity_type, $entity, $langcode, $items, $display) {
    // Data to render:
    $data = $items[0]['value']['local:germplasm crossing block summary'];
    
    // When no cross fround, do not render pane.
    if ($data) {
      // Add element:
      $element[0] = array(
        '#type' => 'markup',
        '#markup' => sprintf('
          <div id="field-germplasm-crossing-block-summary-wrapper">
            <div>
              <ul>
                <li>Year<span>%s</span></li><li>Season<span>%d</span></li>
                <li>%d Crosses</li>
              </ul>
            </div>
          </div>', $data['season'], $data['year'], number_format($data['cross'])),
      );
      
      // Style information.
      drupal_add_css(drupal_get_path('module', 'kp_fields') . '/includes/TripalFields/local__germplasm_crossing_block_summary/theme/style_gcbs_field.css');
    }

    return $element;
  }
}
