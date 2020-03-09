<?php
function AUTO_INCREMENT($nom, $dbh)
{
  $dbh->exec("INSERT INTO Client(Nom) VALUES('$nom')");
}
?>

<?php
$dsn = 'mysql:dbname=web;host=127.0.0.1';
$user = 'monuser';
$password = '123';


try {
$dbh = new PDO($dsn, $user, $password);
//echo "yep ca connecte";
} catch (PDOException $e) {
echo 'Connexion échouée : ' . $e->getMessage();
exit;
}
AUTO_INCREMENT('toto1', $dbh);
//AUTO_INCREMENT('Antoine', $dbh);
//var_dump($dbh->exec("INSERT INTO Client(Nom) VALUES('Antoine')"));
$sql =  'SELECT * FROM Client';
print "<table>";
foreach  ($dbh->query($sql) as $row) {
    echo "<tr>" . "<td>" . $row['numClient'] . "</td>" . "<td>" . $row['Nom'] . "</td>" . "</tr>";
}
print "</table>";

$dbh->lastinsertid();
?>
