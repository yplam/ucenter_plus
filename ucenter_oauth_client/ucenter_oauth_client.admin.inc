<?php

function ucenter_oauth_client_admin_settings(){
  $form['ucenter_oauth_client_use'] = array(
    '#type' => 'radios',
    '#title' => '是否使用OAuth Client接管用户',
    '#description' => '',
    '#options' => array( 0=>'否' , 1=>'是'),
    '#default_value' => variable_get('ucenter_oauth_client_use', 0),
    '#required' => true,
  );
  $form['ucenter_oauth_client_server'] = array(
    '#type' => 'textfield',
    '#title' => '服务器地址',
    '#description' => '请输入使用的UCenter OAuth2 Server地址，如 http://www.example.com/ 以"/"结尾，该网站必须安装UCenter OAuth2 Server',
    '#default_value' => variable_get('ucenter_oauth_client_server', ""),
    '#required' => true,
  );
  $form['ucenter_oauth_client_id'] = array(
    '#type' => 'textfield',
    '#title' => '应用ID',
    '#description' => '',
    '#default_value' => variable_get('ucenter_oauth_client_id', ""),
    '#required' => true,
  );
  $form['ucenter_oauth_client_secret'] = array(
    '#type' => 'textfield',
    '#title' => '应用密钥',
    '#description' => '',
    '#default_value' => variable_get('ucenter_oauth_client_secret', ""),
    '#required' => true,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('save'),
  );

  return $form;
}

function ucenter_oauth_client_admin_settings_validate($form, &$form_state){
  if(!valid_url($form_state['values']['ucenter_oauth_client_server'], TRUE)){
    form_set_error('ucenter_oauth_client_server', t('Please enter a validate url.'));
  }
}

/**
 * save wechat setting config
 */
function ucenter_oauth_client_admin_settings_submit($form, &$form_state){
  foreach($form_state['values'] as $key => $val){
    if(strpos($key, 'ucenter_oauth_client') === 0){
      variable_set($key, $val);
    }
  }
}
