<?php
$dsn = 'mysql:dbname=d1;host=127.0.0.1';
$user = 'monuser';
$password = '123';


try {
$dbh = new PDO($dsn, $user, $password);
} catch (PDOException $e) {
echo 'Connexion échouée : ' . $e->getMessage();
exit;
}


$dbh->query('SELECT * FROM Client;');
var_dump($dbh);
$dbh->prepare();
$dbh->lastinsertid();
