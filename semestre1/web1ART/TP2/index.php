<?php
function AUTO_INCREMENT($nom, $dbh)
{
  $dbh->exec("INSERT INTO Client(Nom) VALUES('$nom')");
}
?>

<!DOCTYPE html>
<html lang="en">
  <head>
    <link rel="stylesheet" href="mycss.css" />
    <title> mon site de TP </title>
    <meta charset="UTF-8">
  </head>
  <body>
    <div class="flex_container">
      <header>
        <div class="flex_child1">
          <div class="img_logo"> <img class="myimg" src="img/logo.png" alt="yaunpbdaffichagedimg"></div>
            <nav>
              <ol>
                <li> <a href="#" title="index">Admin</a></li>
                <li><a href="#" title="monedit">About</a></li>
              </ol>
            </nav>
          </div>
        </header>




      <main>

        <div class="flex_child2">

          <div class="item_left">
            <nav>
              <ol>
                <li> <a href="index.php" title="index">Client</a></li>
                <li><a href="edit.html" title="monedit">Contrat</a></li>
                <li><a href="view.html" title="mnview">Sinistre</a></li>
                <li><a href="view.html" title="mnview">Intervention</a></li>
              </ol>
            </nav>
          </div>



          <div class="item_right">
            <div class="titre_page"><h1> Content </h1></div>
            <section id="section_index">
              <div class="bouton_client"> <p>Ajouter un Client</p> </div>

              <article>

                <!--
                <table>
                  <tr id="firstLineTab">
                    <td>ID</td>
                    <td>Nom</td>
                    <td><a href="#">Actions</a></td>
                  </tr>

                  <tr>
                    <td>1</td>
                    <td>John Doe</td>
                    <td><a href="#">voir modifier</a></td>
                  </tr>

                  <tr>
                    <td>2</td>
                    <td>Jane Doe</td>
                    <td><a href="#">voir modifier</a></td>
                  </tr>

                  <tr>
                    <td>3</td>
                    <td>Jaina Solo</td>
                    <td><a href="#">voir modifier </a></td>
                  </tr>

                  <tr>
                    <td>4</td>
                    <td>Kyle Katarn</td>
                    <td><a href="#">voir modifier </a></td>
                  </tr>

                  <tr>
                    <td>5</td>
                    <td>Satele Shan</td>
                    <td><a href="#">voir modifier </a></td>
                  </tr>

                </table>
              -->
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


                //echo "Hello";
                ?>

              </article>

            </section>

          </div>


          <!--foreach  ($dbh->query($sql) as $row) {
              print "<print $row['Nom'] . "</br>";
          } -->
        </div>
      </main>

      <footer>
        <p>My compagny</p>
      </footer>
    </div>
    <!--https://www.hostinger.fr/tutoriels/creer-un-utilisateur-mysql/ -->



  </body>
</html>
