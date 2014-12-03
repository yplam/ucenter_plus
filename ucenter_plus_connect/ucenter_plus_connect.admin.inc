<?php

function ucenter_plus_connect_admin_settings(){
  $clients = ucenter_plus_connect_get_clients();
  foreach($clients as $key => $client){
    $form[$key] = array(
      '#type' => 'fieldset', 
      '#title' => t('Config ') . $client['title'], 
      '#collapsible' => TRUE, 
      '#collapsed' => $client['enabled'] ? FALSE :TRUE,
    );
    $form[$key]['upc_client_' . $key . '_enabled'] = array(
      '#type' => 'checkbox', 
      '#title' => t('Enabled'), 
      '#default_value' => variable_get('upc_client_' . $key . '_enabled', 0),
    );
    $form[$key]['upc_client_' . $key . '_client_id'] = array(
      '#type' => 'textfield', 
      '#title' => t('Client ID'), 
      '#default_value' => variable_get('upc_client_' . $key . '_client_id', ''),
      '#size' => 60, 
    );
    $form[$key]['upc_client_' . $key . '_client_secret'] = array(
      '#type' => 'textfield', 
      '#title' => t('Client Secret'), 
      '#default_value' => variable_get('upc_client_' . $key . '_client_secret', ''),
      '#size' => 60, 
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('save'),
  );
  return $form;

}


function ucenter_plus_connect_admin_settings_submit($form, &$form_state){
  foreach($form_state['values'] as $key => $val){
    if(strpos($key, 'upc_client_') === 0){
      variable_set($key, $val);
    }
  }
}
