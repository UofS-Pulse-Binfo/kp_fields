<?php
/**
 * @file
 * Materialized view definitions for the fields in this module.
 */

/**
 * MVIEW: organism_counts
 * Counts for all tables with an organism_id broken down by type_id if there is one.
 *
 * @todo add featuremap_organism, organism_pub, polynode_organism?, biomaterial, cell_line
 *
 * @return
 *   The array used by tripal_add_mview() to create this materialized view.
 */
function kp_fields_organism_counts_mview() {
  return array(
    'name' => 'organism_counts',
    'module_name' => 'kp_fields',
    'mv_schema' => array(
      'table' => 'organism_counts',
      'description' => 'Counts for all tables with an organism_id broken down by type_id if there is one.',
      'fields' => array(
        'organism_id' => array(
          'description' => 'The organism the data is associated with.',
          'type' => 'int',
        ),
        'chado_table' => array(
          'description' => 'The chado table the data is stored in.',
          'type' => 'varchar',
          'length' => 255,
        ),
        'cv_id' => array(
          'description' => 'The controlled vocabulary the type is part of.',
          'type' => 'int',
        ),
        'type_id' => array(
          'description' => 'The type of data (foreign key).',
          'type' => 'int',
        ),
        'type_name' => array(
          'description' => 'The type of data (human-readable).',
          'type' => 'varchar',
          'length' => 255,
        ),
        'number' => array(
          'description' => 'The amount of this type of data associated with this organism.',
          'type' => 'int',
        ),
        'organism_count_id' => array(
          'description' => 'The primary key for this table.',
          'type' => 'serial',
        ),
      ),
      'primary key' => array('organism_count_id'),
    ),
    'query' => "
    SELECT organism_id, 'feature' as chado_table, cvt.cv_id as cv_id, type_id as type_id, cvt.name as type_name, count(*) as number
      FROM {feature}
      LEFT JOIN {cvterm} cvt ON cvt.cvterm_id=type_id
      GROUP BY organism_id, type_id, cvt.name, cvt.cv_id
  UNION
    SELECT organism_id, 'stock' as chado_table, cvt.cv_id as cv_id, type_id as type_id, cvt.name as type_name, count(*) as number
      FROM {stock}
      LEFT JOIN {cvterm} cvt ON cvt.cvterm_id=type_id
      GROUP BY organism_id, type_id, cvt.name, cvt.cv_id
  UNION
    SELECT organism_id, 'library' as chado_table, cvt.cv_id as cv_id, type_id as type_id, cvt.name as type_name, count(*) as number
      FROM {library}
      LEFT JOIN {cvterm} cvt ON cvt.cvterm_id=type_id
      GROUP BY organism_id, type_id, cvt.name, cvt.cv_id;
    ",
  );
}

/**
 * MVIEW: organism_marker_counts
 * Amount of each marker type for a given organism.
 *
 * @return
 *   The array used by tripal_add_mview() to create this materialized view.
 */
function kp_fields_organism_marker_counts_mview() {
  return array(
    'name' => 'organism_marker_counts',
    'module_name' => 'kp_fields',
    'mv_schema' => array(
      'table' => 'organism_marker_counts',
      'description' => 'Amount of each marker type for a given organism.',
      'fields' => array(
        'organism_id' => array(
          'description' => 'The organism the data is associated with.',
          'type' => 'int',
        ),
        'type_name' => array(
          'description' => 'The type of data (human-readable).',
          'type' => 'varchar',
          'length' => 255,
        ),
        'number' => array(
          'description' => 'The amount of this type of data associated with this organism.',
          'type' => 'int',
        ),
        'organism_marker_count_id' => array(
          'description' => 'The primary key for this table.',
          'type' => 'serial',
        ),
      ),
      'primary key' => array('organism_marker_count_id'),
    ),
    'query' => "
    SELECT f.organism_id, prop.value as type_name, count(*) as number
    FROM chado.feature f
    LEFT JOIN chado.featureprop prop ON prop.feature_id=f.feature_id
      AND prop.type_id IN (SELECT cvterm_id FROM chado.cvterm WHERE name='marker_type')
    WHERE
      f.type_id IN (SELECT cvterm_id FROM chado.cvterm WHERE name='genetic_marker')
    GROUP BY f.organism_id, prop.value
    ",
  );
}
