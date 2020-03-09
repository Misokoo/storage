

Section Partie1.


Theorem A_imp_A: forall A : Prop, A -> A.
Proof.
intro.
intro preuve_de_A.
assumption.
Qed.


Theorem forward_small : 
(forall A B : Prop, A -> (A->B) -> B).
Proof.
intros A B.
intro preuve_de_A.
intro preuve_A_imp_B.
apply preuve_A_imp_B.
assumption.
Qed.


Theorem backward_small : 
(forall A B : Prop, A -> (A->B) -> B).
Proof.
intros A B.
intro.
intro.
apply H0 in H.
assumption.
Qed.


Check Prop.
Check (forall A: Prop, A -> A).

Theorem A_imp_A_encore: 
forall A : Prop, A -> A.
Proof.
admit.
Admitted.


Print False.
Print True.
Check I.


Theorem False_cannot_be_proven : ~False.
Proof.
intro.
assumption.
Qed.


Theorem thm_false_imp_true : False -> True.
Proof.
intro.
exact I.
Qed.





(* Encore un th\u00e9or\u00e8me *)

Theorem thm_false_imp_true_2 : False -> True.
Proof.
intro.
exact I.
Qed.


Theorem thm_true_imp_false :
 ~(True -> False).
Proof.
intro.
apply H.
apply I.
Qed.


Theorem I2: forall A B C : Prop, 
(A -> B) -> (B -> C) -> A -> C.
Proof.
tauto.
Qed.


Theorem I3: forall A B : Prop, 
A /\ B <-> B /\ A.
Proof.
intros A B.
split.
- intro.
  split.
  * destruct H.
    exact H0.
  * destruct H.
    exact H.
- intro.
  destruct H.
  split.
  * exact H0.
  * exact H.
Qed.


Lemma E1F4 : forall A B : Prop,
 A \/ B <-> B \/ A.
Proof.
intros A B.
split.
intro.
destruct H.
right.
exact H.
left.
exact H.
intro.
destruct H.
right.
exact H.
left.
exact H.
Qed.


Lemma E1F5 : forall A B C : Prop, 
(A /\ B) /\ C <-> A /\ (B /\ C).
Proof.
intros A B C.
split.
intro.
split.
destruct H.
destruct H.
exact H.



Qed.


Lemma E1F7 : forall A : Prop, A -> ~~A.
Proof.
intro.
intro.
intro.
elim H0.
assumption.
Qed.


(*
Lemma E1F6 : forall A B C : Prop, 
(A \/ B) \/ C <-> A \/ (B \/ C).
*)


Lemma E1F8 : forall A B : Prop, (A -> B) -> ~B -> ~A.
Proof.
Qed.


Lemma E1F9 : forall A : Prop, ~~(A \/ ~A).
Proof.
Qed.

End Partie1.

Section Partie2.


Definition peirce := forall P Q:Prop, ((P->Q)->P)->P.
Definition classic := forall P:Prop, ~~ P -> P.
Definition excluded_middle := forall P:Prop, P \/ ~P.
Definition de_morgan_not_and_not := forall P Q:Prop, ~(~P/\~Q)->P\/Q.
Definition implies_to_or := forall P Q:Prop, (P->Q)->(~P\/Q).



Lemma emd_class : excluded_middle -> classic.
Proof.
Qed.


Lemma emd_morgan : excluded_middle ->
 de_morgan_not_and_not.
Proof.
Qed.



Lemma class_emd : classic -> excluded_middle.
Proof.
Qed.
End Partie2.




Section Partie3.


Inductive alphabet := | a | b.

Inductive mot := 
| mot_vide : mot
| base : alphabet -> mot
| concat : mot -> mot -> mot.

Check concat (base b) (base a).

Inductive palindrome : mot ->  Prop :=
| palindrom_vide: palindrome mot_vide
| palindrom_etendu: forall m: mot, palindrome m -> palindrome (concat (base a) (concat m (base a))).

End Partie3.
