<?php

/**
 * wechat setting form
 */
function ucenter_plus_admin_settings(){
  $form['ucenter_plus_config_use'] = array(
    '#type' => 'radios',
    '#title' => '是否使用UCENTER',
    '#description' => '',
    '#options' => array( 0=>'否' , 1=>'是'),
    '#default_value' => variable_get('ucenter_plus_config_use', 0),
    '#required' => true,
  );
  $form['ucenter_plus_config_host'] = array(
    '#type' => 'textfield',
    '#title' => '数据库地址',
    '#description' => '',
    '#default_value' => variable_get('ucenter_plus_config_host', ""),
    '#required' => true,
  );
  $form['ucenter_plus_config_user'] = array(
    '#type' => 'textfield',
    '#title' => '数据库用户名',
    '#description' => '',
    '#default_value' => variable_get('ucenter_plus_config_user', ""),
    '#required' => true,
  );
  $form['ucenter_plus_config_pass'] = array(
    '#type' => 'password',
    '#title' => '数据库密码',
    '#description' => '',
    '#required' => false,
  );
  $form['ucenter_plus_config_name'] = array(
    '#type' => 'textfield',
    '#title' => '数据库名称',
    '#description' => '',
    '#default_value' => variable_get('ucenter_plus_config_name', ""),
    '#required' => true,
  );
  $form['ucenter_plus_config_charset'] = array(
    '#type' => 'textfield',
    '#title' => '数据库编码',
    '#description' => '',
    '#default_value' => variable_get('ucenter_plus_config_charset', "utf8"),
    '#required' => true,
  );
  $form['ucenter_plus_config_pre'] = array(
    '#type' => 'textfield',
    '#title' => '数据库前缀',
    '#description' => '',
    '#default_value' => variable_get('ucenter_plus_config_pre', ""),
    '#required' => true,
  );
  $form['ucenter_plus_config_key'] = array(
    '#type' => 'textfield',
    '#title' => 'UCENTER KEY',
    '#description' => '',
    '#default_value' => variable_get('ucenter_plus_config_key', ""),
    '#required' => true,
  );
  $form['ucenter_plus_config_api'] = array(
    '#type' => 'textfield',
    '#title' => 'UCENTER API',
    '#description' => '',
    '#default_value' => variable_get('ucenter_plus_config_api', ""),
    '#required' => true,
  );
  $form['ucenter_plus_config_ip'] = array(
    '#type' => 'textfield',
    '#title' => 'UC_IP',
    '#description' => '',
    '#default_value' => variable_get('ucenter_plus_config_ip', ""),
    '#required' => true,
  );
  $form['ucenter_plus_config_appid'] = array(
    '#type' => 'textfield',
    '#title' => 'UCENTER APP ID',
    '#description' => '',
    '#default_value' => variable_get('ucenter_plus_config_appid', ""),
    '#required' => true,
  );
  $form['ucenter_plus_config_ppp'] = array(
    '#type' => 'textfield',
    '#title' => 'UCENTER PPP',
    '#description' => '',
    '#default_value' => variable_get('ucenter_plus_config_ppp', ""),
    '#required' => true,
  );


  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('save'),
  );

  return $form;
}

/**
 * save wechat setting config
 */
function ucenter_plus_admin_settings_submit($form, &$form_state){
  if(!empty($form_state['values']['ucenter_plus_config_pass'])){
    variable_set('ucenter_plus_config_pass', $form_state['values']['ucenter_plus_config_pass']);
  }
  unset($form_state['values']['ucenter_plus_config_pass']);
  foreach($form_state['values'] as $key => $val){
    if(strpos($key, 'ucenter_plus_config') === 0){
      variable_set($key, $val);
    }
  }
}
