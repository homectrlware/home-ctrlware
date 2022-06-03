<?php
error_reporting(0);
$mysql_servername = "YOUR SERVER NAME";
$mysql_username = "YOUR SERVER USERNAME" ;
$mysql_password = "YOUR SERVER PASSWORD";
$mysql_databse = "DATABASE NAME";
$conn=mysqli_connect($mysql_servername,$mysql_username,$mysql_password,$mysql_database);
$serial = $_GET['serial']?:"null";
if(isset( $_GET['value1']) && isset( $_GET['value2'])){
    $value1 = $_GET['value1']?:"0";
    $value2 = $_GET['value2']?:"0";
    $query = "update data set value1=$value1, value2=$value2 where serial='$serial';";
}
else if(isset($_GET['value1'])){
    $value1 = $_GET['value1']?:"0";
    $query = "update data set value1=$value1 where serial='$serial';";
}
else if(isset($_GET['value2'])){
    $value2 = $_GET['value2']?:"0";
    $query = "update data set value2=$value2 where serial='$serial';";
}
if(mysqli_query($conn,$query))
{
    echo "good";
}
else{
    echo "bad";
}
?>