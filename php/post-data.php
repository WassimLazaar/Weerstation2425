<?php

/*
    Mike van Kuijk - 2024
*/

$servername = "localhost"; // Database host
$dbname = "weerstation"; // Database name
$username = "root"; // Database username
$password = ""; // Database password
$api_key_value = "ESPIsAFunDevice12345"; //Create API key as extra security

$api_key = $temperature = $humidity = $pressure = ""; //Define all variables as strings

//Returns method used in the URL (checks if its POST)
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    //Checks if api_key is in post url
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
        $temperature = test_input($_POST["temperature"]); //Assign temp variable from url &temperature
        $humidity = test_input($_POST["humidity"]); //Assign temp variable from url &humidity
        $pressure = test_input($_POST["pressure"]); //Assign temp variable from url &pressure
        
        // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        
        //store the data in variable so it eventually can send to database
        $sql = "INSERT INTO tbldata (TEMPERATURE, HUMIDITY, PRESSURE)
        VALUES ('" . $temperature . "', '" . $humidity . "', '" . $pressure . "')";
        
        //Checks if query is correctly handled and excecuted
        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error; //error message if data couldnt be processed
        }
    
        $conn->close();//close database connection
    }
    else {
        echo "Wrong API Key provided."; //API key doesnt correspond
    }

}
else {
    echo "No data posted with HTTP POST."; //The URL doesnt consist out of a POST METHOD
}

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}