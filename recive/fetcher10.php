<?php
$servername = "localhost";
$username = "root";
$password= "";
$dbname = "counter";

// Create connection
$link = mysqli_connect($servername, $username, $password, $dbname) or die("teknis");

$sql = "SELECT status FROM loker WHERE id = '10'"; 
$query= mysqli_query($link, $sql);

while($row = mysqli_fetch_array($query))
{
	echo $row['status']."";
}

//mysqli_close($conn); 
?>