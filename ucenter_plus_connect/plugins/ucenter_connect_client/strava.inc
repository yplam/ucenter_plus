<?php

$plugin = array(
  'name' => 'strava',
  'title' => t('Sign in with Strava'),
  'description' => t('Use Strava account login'),
  'callback' => 'ucenter_oauth_client_strava',
  'authorize_uri' => 'https://www.strava.com/oauth/authorize',
  'access_token_uri' => 'https://www.strava.com/oauth/token',
  'info_uri' => 'https://www.strava.com/api/v3/athlete',
  'icon' => 'strava.png',
  
);


/**
 * Implements hook_csna_provider_callback().
 */
function ucenter_oauth_client_strava($client, $request) {
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
    if (!isset($data->access_token)) {
      return FALSE;
    }
    return array(
      'access_token' => $data->access_token,
      'uid' => $data->athlete->id,
      'name' => $data->athlete->firstname.$data->athlete->lastname,
      'email' => $data->athlete->email
    );
  }
}




