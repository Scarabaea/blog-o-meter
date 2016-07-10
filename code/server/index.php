
<?php


function getService($email, $k)
{
  // Creates and returns the Analytics service object.

  // Load the Google API PHP Client Library.
  require_once 'src/Google/autoload.php';




  // Use the developers console and replace the values with your
  // service account email, and relative location of your key file.
  $service_account_email = $email;
  $key_file_location = $k;

  // Create and configure a new client object.
  $client = new Google_Client();
  $client->setApplicationName("HelloAnalytics");
  $analytics = new Google_Service_Analytics($client);

  // Read the generated client_secrets.p12 key.
  $key = file_get_contents($key_file_location);
  $cred = new Google_Auth_AssertionCredentials(
      $service_account_email,
      array(Google_Service_Analytics::ANALYTICS_READONLY),
      $key
  );
  $client->setAssertionCredentials($cred);
  if($client->getAuth()->isAccessTokenExpired()) {
    $client->getAuth()->refreshTokenWithAssertion($cred);
  }

  return $analytics;
}
  


//website 1
$email = 'account@.gserviceaccount.com';
$key = 'keyfile.p12';
$GA_VIEW_ID = 'ga:XXXXXXX';
$service = getService($email, $key);
try {
    $result = $service->data_realtime->get(
        $GA_VIEW_ID,
        'rt:activeVisitors'
    );
    $site1 = $result->totalsForAllResults['rt:activeVisitors'];
    //echo $count;
} catch(Exception $e) {
    var_dump($e);
}




//Website2
$email = 'account@.gserviceaccount.com';
$key = 'keyfile.p12';
$GA_VIEW_ID = 'ga:XXXXXXX';
$service = getService($email, $key);
try {
    $result = $service->data_realtime->get(
        $GA_VIEW_ID,
        'rt:activeVisitors'
    );
    $site2 = $result->totalsForAllResults['rt:activeVisitors'];
    //echo $count;
} catch(Exception $e) {
    var_dump($e);
}

echo $site1 . ";" . $site2;
//echo $bleep;