<?php
include('inc/header.php');


?>


<?php
function Redirect2($url, $permanent = false)
{
    if (headers_sent() === false)
    {
        header('Location: ' . $url, true, ($permanent === true) ? 301 : 302);
    }

    exit();
}

Redirect2('https://www.grandage.website/jeelizFaceFilter/demos/canvas2D/faceTrack/', false);
?>