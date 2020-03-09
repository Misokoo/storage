Lemma exemple (A : Prop) :  A -> A.
Proof.
tauto.
Qed.

Lemma hilbertS (A B C : Prop) :  (A -> B -> C) -> (A -> B) -> A -> C.
Proof.
tauto.
Qed.





Section Partie1.

Lemma q2 (A B : Prop) :  A -> (B -> A).
Proof.
tauto.
Qed.

Lemma q3 (A B : Prop) :  A -> (~A -> B).
Proof.
tauto.
Qed.

Lemma q4 (A B C : Prop) :  (A -> B) -> ((B -> C) -> (A -> C)).
Proof.
tauto.
Qed.

Lemma q5 (A B : Prop) :  (A -> B) -> (~B -> ~A).
Proof.
tauto.
Qed.


Require Import Classical.



Lemma tiersexclus (A : Prop) : A \/ ~A.
Proof.
tauto.
Qed.


Lemma tiersexclus2 (A : Prop) : A \/ ~A.
Proof.
tauto.
Qed.

Lemma bottom_c (A : Prop) : (~A -> False) -> A.
Proof.
tauto.
Qed.

Lemma q8 (A B : Prop) : (~B -> ~A) -> (A -> B).
Proof.
tauto.
Qed.

Lemma q9 (A : Prop) : ~~A <-> A.
Proof.
tauto.
Qed.

Lemma q10 (A : Prop) :  (A /\ ~A) <-> False.
Proof.
tauto.
Qed.

Lemma q11 (A B : Prop) :  (A \/ B) <-> ~(~A /\ ~B).
Proof.
tauto.
Qed.
 
Lemma q12 (A : Prop) :  ~A <-> (A -> False).
Proof.
tauto.
Qed.

Lemma q13 (A B : Prop) :  (A <-> B) <-> (A -> B) /\ (B -> A).
Proof.
tauto.
Qed.

Lemma q14 (A B C : Prop) :  (A /\ B -> C) <-> (A -> B -> C).
Proof.
tauto.
Qed.



Lemma q15 (A B C : Prop) :  (C -> A)\/ (C -> B) <-> (C -> A \/ B).
Proof.
tauto.
Qed.

Lemma tiersexclus_regle (A B : Prop) : (((A \/ ~A) -> B) -> B).
Proof.
tauto.
Qed.

Lemma mp (A B : Prop) : A -> (A -> B) -> B.
Proof.
tauto.
Qed.


Lemma q15_2 (A B C : Prop) :  (C -> A \/ B) -> (C -> A)\/ (C -> B).
Proof.
tauto.
Qed.


Lemma q15_3 (A B C : Prop) :  (C -> A \/ B) -> (C -> A)\/ (C -> B).
Proof.
tauto.
Qed.

Lemma q15_3_2 (A B C : Prop) :  (C -> A \/ B) -> (C -> A)\/ (C -> B).
Proof.
tauto.
Qed.

Lemma q15_4 (A B C : Prop) :  (C -> A \/ B) -> (C -> A)\/ (C -> B).
Proof.
tauto.
Qed.


Lemma q16 (A B : Prop) : ~ (A /\ B) -> (~ A \/ ~ B).
Proof.
tauto.
Qed.

End Partie1.



Section Partie2.

Lemma q17 (X : Type) : forall (x1 x2 : X), x1 = x2 -> x2 = x1.



Lemma q18 (X : Type) : forall (x1 x2 x3 : X), x1 = x2 /\ x2 = x3 -> x1 = x3.


End Partie2.




Section Partie3.


Lemma q19 (X : Type) (A B : X -> Prop) :
  ((forall x, A x) \/ (forall x, B x)) -> forall x, A x \/ B x.
Proof.
tauto.
Qed.


Lemma q20 (X : Type) (A B : X -> Prop) :
  (exists x, A x /\ B x) -> ((exists x, A x) /\ (exists x, B x)).
Proof.
tauto.
Qed.



Variables 
 (A:Type)
 (P Q:A -> Prop).



Lemma ex_or : (exists x:A, P x \/ Q x) -> ex P \/ ex Q.
Proof.
tauto.
Qed.
 
Lemma ex_or_R : ex P \/ ex Q -> (exists x:A, P x \/ Q x).
Proof.
tauto.
Qed.

Lemma two_is_three : 
(exists x:A, forall R : A->Prop, R x) -> 2 = 3.
Proof.
tauto.
Qed.

Lemma forall_no_ex : (forall x:A, P x) -> ~(exists y:A, ~ P y).
Proof.
tauto.
Qed.

End Partie3.




