<?php
$mysql_servername = "YOUR SERVER NAME";
$mysql_username = "YOUR SERVER USERNAME" ;
$mysql_password = "YOUR SERVER PASSWORD";
$mysql_databse = "DATABASE NAME";
$conn=mysqli_connect($mysql_servername,$mysql_username,$mysql_password,$mysql_database);
$uname = $_GET['username'];
$pass = $_GET['password'];
$query = "select username from data where serial='$serial';";
$result = mysqli_query($conn,$query);
if(mysqli_num_rows($result)>0){
    echo "good";
}
else{
    echo "bad";
}
?>