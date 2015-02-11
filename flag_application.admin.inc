<?php
/**
 * @file
 * Flag Application Administration.
 */

 function flag_application_form($form, $form_state) {
 	$form = new Array();

 	$header = array(
 		'title' => t('Flagged Contennt'),
 		'name' => t('Username'),
 		'entity_id' => t('Node ID'),
 		'uid' => t('User ID'),
 		'flagging_id' => t('Flag ID'),
 		'status' => t('Status'),
 	);

 	$query = db_select('flag_application', 'fa')->extend('PagerDefault');
	$query = $query->join('flagging', 'f', f.flagging_id = fa.flagging_id);
	$query = $query->join('node', 'n', f.entity_id = n.nid);
	$query = $query->join('users', 'u', f.uid = u.uid);
	$query->fields('fa', array('status'))
		->fields('f', array('entity_id', 'timestamp', 'created', 'flagging_id'))
		->fields('n', array('title'))
		->fields('u', array('name', 'uid'))
		->orderBy('timestamp', 'DESC')
		->limit(25);
	$results = $query->execute();

	$rows = array();

	foreach ($results as $result) {
		switch ($result->status) {
			case 0:
				$status = 'Pending';
				break;
			case 1:
				$status = 'Approved';
				break;
			case 2:
				$status = 'Denied';
				break;
			default:
				break;
		}

		$rows[] = array(
			'title' => l($result->title, 'node/'.$result->entity_id),
			'name' => l($result->name, 'node/'.$result->uid),
			'entity_id' => $result->entity_id),
			'uid' => $result->uid,
			'flagging_id' => $result->flagging_id,
			'status' => $status,
			'#attributes' => array('class' => array('application-row')),
		);
	}

	$form['flag_application_status']['approvedeny'] = array(
		'#type' => 'select'	,
		'#title' => 'Actions',
		'#options' => array(
			1 => t('Approve'),
			2 => t('Deny'),
		),

	);

	$form['flag_application_table'] = array(
		'#type' => 'tableselect'	,
		'#header' => $header,
		'#options' => $rows,
		'#empty' => t('No applicants found.'),
		'#attributes' => array('class' => array('applications'),
	);

	$form['pager'] = array('#markup' => theme('pager'));

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
	);

	return $form;
}
?>