<?php
$dsn = 'mysql:dbname=web;host=127.0.0.1';
$user = 'monuser';
$password = '123';


try {
$dbh = new PDO($dsn, $user, $password);
echo "yep ca connecte";
} catch (PDOException $e) {
echo 'Connexion échouée : ' . $e->getMessage();
exit;
}

$sql =  'SELECT * FROM Client';
foreach  ($dbh->query($sql) as $row) {
    print $row['Nom'] . "</br>";
}



$dbh->lastinsertid();


echo "Hello";
?>
