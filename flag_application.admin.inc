
/**
 * @file
 * Flag Application Administration.
 */

 function flag_application_form($form, $form_state) {
 	$form = new Array();
 	$query = db_select('flag_application', 'fa')->extend('PagerDefault');
	$query = $query->join('flagging', 'f', 'f.flagging_id = fa.flagging_id);
	$query = $query->join('node', 'n', 'f.entity_id = n.nid);
	$query = $query->join('users', 'u', 'f.uid = u.uid);
	$query->fields('fa', array('status'))
		->fields('f', array('entity_id', 'timestamp', 'created', 'flagging_id'))
		->fields('n', array('title'))
		->fields('u', array('name', 'uid'))
		->orderBy('timestamp', 'DESC')
		->limit(25);
	$results = $query->execute();

	$txt = ""

	foreach($results as $result){
		$txt .= ' ' . $result->title; 
		$txt .= ' ' . $result->name; 
		$txt .= ' ' . $result->entity_id; 
		$txt .= ' ' . $result->uid; 
		$txt .= ' ' . $result->flagging_id; 
		$txt .= ' ' . $result->status; 
		$txt .= '<br />' ; 
	}

	$form['txt']['#markup'] = $txt;
	return $form;
}
?>