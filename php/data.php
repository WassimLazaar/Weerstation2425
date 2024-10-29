<head>
  <link rel="stylesheet" href="style.css">
</head>
<header>
  <h1>Raw Data From BME280</h1>
</header>
<body>
<?php
$servername = "localhost"; // Database host
$dbname = "weerstation"; // Database name
$username = "root"; // Database username
$password = ""; // Database password

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Query to get data from database
$sql = "SELECT ID, TEMPERATURE, HUMIDITY, PRESSURE, TIME_STAMP FROM tbldata ORDER BY ID DESC";

//create table in HTML on webpage with table headers
echo '<table cellspacing="5" cellpadding="5">
      <tr> 
        <th>ID</th> 
        <th>TEMPERATURE</th> 
        <th>HUMIDITY</th>
        <th>PRESSURE</th> 
        <th>TIMESTAMP</th> 
      </tr>';
 
//if the qurey retrieval succeeded show the rows    
if ($result = $conn->query($sql)) {
    //output data for each row fetch_assoc is like a array with values in it (loops thorugh array and retrieves data)
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["ID"];
        $row_temperature = $row["TEMPERATURE"];
        $row_humidity = $row["HUMIDITY"]; 
        $row_pressure = $row["PRESSURE"]; 
        $row_reading_time = $row["TIME_STAMP"];
      
        //print the variables into the table
        echo '<tr> 
                <td>' . $row_id . '</td> 
                <td>' . $row_temperature .  ' &#x2103</td> 
                <td>' . $row_humidity . ' %</td>
                <td>' . $row_pressure . ' hPa</td> 
                <td>' . $row_reading_time . '</td> 
              </tr>';
    }
    $result->free();
}

$conn->close();
?> 
</table>
</body>
</html>
