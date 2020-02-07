<?php
// db initialization

$servername = "localhost";

$username = "root";

$password = "134625";

$dbname = "lunapot";

date_default_timezone_set('Asia/Seoul');

// Check connection

$con = new mysqli($servername, $username, $password, $dbname);

if ($con->connect_error) {

  die("Connection failed: " . $con->connect_error);

}

?>

<!DOCTYPE HTML>

<html>

<head>

 <meta charset="utf-8">

 <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>

 <script type="text/javascript">

 google.charts.load('current', {packages:['corechart']});

 google.charts.setOnLoadCallback(drawChart);

 function drawChart() {

        var data = google.visualization.arrayToDataTable([

        ['Date', 'Temperature', 'Humidity', 'Soil'],

        <?php

        $query = "SELECT * From sens_table order by sensDate desc LIMIT 0, 8";

        $exec = mysqli_query($con,$query);

        while($row = mysqli_fetch_array($exec)){

               echo "['" . $row['sensDate'] . "'," . $row['temperature']. "," . $row['humidity']. ",". $row['soil']."],";

        }

        ?>

        ]);

        var options = {

               title: 'Sensor Data',

               colors: ['#e0440e', '#e6693e', '#ec8f6e'],

               curveType: 'function',

               legend: {position: 'bottom'},

               hAxis: {direction: -1}

               }

               vAxis: {

                       viewWindow: {

                              min: -10

                       }

        };

        var chart = new google.visualization.LineChart(document.getElementById('curve_chart'));

        chart.draw(data, options);

 }

 </script>

</head>

<body>

<center>

 <h1> 나의 LUNAPOT </h1>

 <div id="curve_chart" style="width: 1000px; height: 450px;"></div> #1000 450

</center>

</body>

</html>


