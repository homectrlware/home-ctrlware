<?php
$mysql_servername = "YOUR SERVER NAME";
$mysql_username = "YOUR SERVER USERNAME" ;
$mysql_password = "YOUR SERVER PASSWORD";
$mysql_databse = "DATABASE NAME";
$conn=mysqli_connect($mysql_servername,$mysql_username,$mysql_password,$mysql_database);
$serial = $_GET['serial'];
$username = $_GET['username'];
$name = $_GET['name'];
$query = "insert into data values('$serial','$username','$name',0,0);";
if(mysqli_query($conn,$query)){
    echo "good";
}
else{
    echo "bad";
}
?>