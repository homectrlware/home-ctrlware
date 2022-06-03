<?php
$mysql_servername = "YOUR SERVER NAME";
$mysql_username = "YOUR SERVER USERNAME" ;
$mysql_password = "YOUR SERVER PASSWORD";
$mysql_databse = "DATABASE NAME";
$conn=mysqli_connect($mysql_servername,$mysql_username,$mysql_password,$mysql_database);
$password = $_GET['password'];
$username = $_GET['username'];
$name = $_GET['name'];
$query = "insert into user values('$name','$username','$password');";
if(mysqli_query($conn,$query)){
    echo "good";
}
else{
    echo "bad";
}
?>