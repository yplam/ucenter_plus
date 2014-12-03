<?php

/**
 * ucenter 事件响应入口
 */
function ucenter_plus_ucapi() {
  _ucenter_plus_init();
  $code = isset($_GET['code']) ? $_GET['code'] : '';
  parse_str(uc_authcode($code, 'DECODE', UC_KEY), $get);
  $get = uc_stripslashes($get);

  if(empty($get) || empty($get['time'])) {
    exit('Invalid Request');
  }

  if(time() - $get['time'] > 3600) {
    exit('Authracation has expiried');
  }

  $action = isset($get['action']) ? $get['action'] : '';
  switch ($action) {
    case 'test':
      exit(UC_API_RETURN_SUCCEED);
    case 'synlogout' :
      _ucenter_plus_api_synlogout();
      break;
    case 'synlogin' :
      _ucenter_plus_api_synlogin($get['uid']);
      break;
    case 'deleteuser' :
      _ucenter_plus_api_deleteuser($get['ids']);
      break;
    case 'renameuser' :
      _ucenter_plus_api_renameuser($get['uid'], $get['newusername']);
      break;
    case 'updatepw':
      _ucenter_plus_api_updatepw($get['username'], $get['password']);
      break;
    case 'updatebadwords':
      _ucenter_plus_api_updatebadwords();
      break;
    case 'updatehosts':
      _ucenter_plus_api_updatehosts();
      break;
    case 'updateapps':
      _ucenter_plus_api_updateapps();
      break;
    case 'updateclient':
      _ucenter_plus_api_updateclient();
      break;
    default :
      watchdog('ucenter_plus', 'untouch '.$action);
  }
  exit(UC_API_RETURN_FORBIDDEN);
}

/**
 * 同步退出
 */
function _ucenter_plus_api_synlogout() {
  global $user;
  if(!$user->uid){
    exit(UC_API_RETURN_SUCCEED);
  }
  watchdog('ucenter_plus', 'Session closed for %name.', array('%name' => $user->name));
  module_invoke_all('user_logout', $user);
  session_destroy();
  exit(UC_API_RETURN_SUCCEED);
}

/**
 * ucenter sync login
 * create user if not exists
 * share the same ID
 */
function _ucenter_plus_api_synlogin($ucuid) {
  global $user;
  if(!$ucuid){
    exit(UC_API_RETURN_FAILED);
  }
  $user = user_load((int)$ucuid);
  if($user){
    drupal_session_regenerate();
    exit(UC_API_RETURN_SUCCEED);
  }

  // need to create the user from ucenter and login
  // 0 uid, 1 username , 2 email
  list($ucuid, $name, $mail) = uc_get_user($ucuid, 1);
  if(empty($ucuid)) {
    exit(UC_API_RETURN_FAILED);
  }
  $edit = array(
    'name' => _ucenter_plus_from_string($ucname),
    'mail' => _ucenter_plus_from_string($ucmail),
    'ucuid' => _ucenter_plus_from_string($ucuid)
  );
  $account = _ucenter_plus_user_create($edit);
  if(!$account){
    exit(UC_API_RETURN_FAILED);
  }
  global $user;
  $user = $account;
  drupal_session_regenerate();
  exit(UC_API_RETURN_SUCCEED);
}

/**
 * user delete users event
 * @param $ids user id string
 */
function _ucenter_plus_api_deleteuser($ids) {
  $ids = explode(',', $ids);
  user_delete_multiple($ids);
  exit(UC_API_RETURN_SUCCEED);
}

/**
 * 修改用户名
 */
function _ucenter_plus_api_renameuser($ucuid, $username) {
  $ucuid = (int)$ucuid;
  $cuser = user_load($ucuid);
  if(!$cuser) {
    exit(UC_API_RETURN_FAILED);
  }
  if (user_save($cuser, array('name' => _ucenter_plus_from_string($username)), 'ucenter_plus')) {
    exit(UC_API_RETURN_SUCCEED);
  }
  else {
    exit(UC_API_RETURN_FAILED);
  }
}

function _ucenter_plus_api_updatepw($username, $password) {
  $cuser = user_load_by_name(_ucenter_plus_from_string($username));
  if(!$cuser) {
    exit(UC_API_RETURN_FAILED);
  }
  if (user_save($cuser, array('pass' => _ucenter_plus_from_string($password)), 'ucenter_plus')) {
    exit(UC_API_RETURN_SUCCEED);
  }
  else {
    exit(UC_API_RETURN_FAILED);
  }
}

function _ucenter_plus_api_updatebadwords(){
  $post = uc_unserialize(file_get_contents('php://input'));
  $cachefile = UC_DATADIR.'cache/badwords.php';
  $fp = fopen($cachefile, 'w');
  $s = "<?php\r\n";
  $s .= '$_CACHE[\'badwords\'] = '.var_export($post, TRUE).";\r\n";
  fwrite($fp, $s);
  fclose($fp);
  exit(API_RETURN_SUCCEED);
}

function _ucenter_plus_api_updatehosts(){
  $post = uc_unserialize(file_get_contents('php://input'));
  $cachefile = UC_DATADIR.'cache/hosts.php';
  $fp = fopen($cachefile, 'w');
  $s = "<?php\r\n";
  $s .= '$_CACHE[\'hosts\'] = '.var_export($post, TRUE).";\r\n";
  fwrite($fp, $s);
  fclose($fp);
  exit(API_RETURN_SUCCEED);
}


function _ucenter_plus_api_updateapps(){
  $post = uc_unserialize(file_get_contents('php://input'));
  $cachefile = UC_DATADIR.'cache/apps.php';
  $fp = fopen($cachefile, 'w');
  $s = "<?php\r\n";
  $s .= '$_CACHE[\'apps\'] = '.var_export($post, TRUE).";\r\n";
  fwrite($fp, $s);
  fclose($fp);
  exit(API_RETURN_SUCCEED);
}

function _ucenter_plus_api_updateclient(){
  $post = uc_unserialize(file_get_contents('php://input'));
  $cachefile = UC_DATADIR.'cache/setting.php';
  $fp = fopen($cachefile, 'w');
  $s = "<?php\r\n";
  $s .= '$_CACHE[\'setting\'] = '.var_export($post, TRUE).";\r\n";
  fwrite($fp, $s);
  fclose($fp);
  exit(API_RETURN_SUCCEED);
}

