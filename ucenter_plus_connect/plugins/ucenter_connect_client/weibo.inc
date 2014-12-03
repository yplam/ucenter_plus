<?php

$plugin = array(
  'name' => 'weibo',
  'title' => t('Sign in with Weibo'),
  'description' => t('Use Weibo account login'),
  'callback' => 'ucenter_oauth_client_weibo',
  'authorize_uri' => 'https://api.weibo.com/oauth2/authorize',
  'access_token_uri' => 'https://api.weibo.com/oauth2/access_token',
  'info_uri' => 'https://api.weibo.com/2/users/show.json',
  'icon' => 'weibo_126x24.png',
  
);


/**
 * Implements hook_csna_provider_callback().
 */
function ucenter_oauth_client_weibo($client, $request) {
  if (isset($request['code'])) {
    $parameters = array(
      'client_id' => $client['client_id'],
      'client_secret' => $client['client_secret'],
      'grant_type' => 'authorization_code',
      'redirect_uri' => $client['redirect_uri'],
      'code' => $request['code'],
    );

    $param_data = array(
      'method' => 'POST',
      'data' => drupal_http_build_query($parameters),
    );

    $http = drupal_http_request(url($client['access_token_uri'], array('query' => $parameters)), $param_data);

    $data = json_decode($http->data);
    $http = drupal_http_request(url($client['info_uri'], array('query' => array('access_token' => $data->access_token, 'uid' => $data->uid))));
    $info = json_decode($http->data);
    if (!isset($info->id)) {
      return FALSE;
    }
    return array(
      'access_token' => $data->access_token,
      'uid' => $info->id,
      'name' => $info->name,
    );
  }
}




