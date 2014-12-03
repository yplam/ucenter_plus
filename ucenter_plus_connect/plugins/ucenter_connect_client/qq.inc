<?php

$plugin = array(
  'name' => 'qq',
  'title' => t('Sign in with QQ'),
  'description' => t('Use QQ account login'),
  'callback' => 'ucenter_oauth_client_qq',
  'authorize_uri' => 'https://graph.qq.com/oauth2.0/authorize',
  'access_token_uri' => 'https://graph.qq.com/oauth2.0/token',
  'info_uri' => 'https://graph.qq.com/user/get_user_info',
  'icon' => 'qq_120x24.png',
  
);


/**
 * Implements hook_csna_provider_callback().
 */
function ucenter_oauth_client_qq($client, $request) {
  if (isset($request['code'])) {
    $parameters = array(
      'client_id' => $client['client_id'],
      'client_secret' => $client['client_secret'],
      'grant_type' => 'authorization_code',
      'redirect_uri' => $client['redirect_uri'],
      'code' => $request['code'],
    );

    $param_data = array(
      'method' => 'GET',
      'data' => drupal_http_build_query($parameters),
    );

    $http = drupal_http_request(url($client['access_token_uri'], array('query' => $parameters)), $param_data);
    $data = explode('&', $http->data);
    $data = explode('=', reset($data));
    if(empty($data[1])){
      return FALSE;
    }
    $http = drupal_http_request('https://graph.qq.com/oauth2.0/me?' . $http->data);
    preg_match('/\{[^\}]*\}/', $http->data, $obj);
    $openid = json_decode($obj[0]);
    if(empty($openid->openid)){
      return FALSE;
    }
    $http   = drupal_http_request(url($client['info_uri'], array(
      'query' => array(
      'access_token' => $data[1],
      'oauth_consumer_key' => $client['client_id'],
      'openid' => $openid->openid,))));
    $info   = json_decode($http->data);
    if(empty($info)){
      return FALSE;
    }
    return array(
      'access_token' => $data[1],
      'uid' => $openid->openid,
      'name' => $info->nickname,
    );
   
  }
}



