

*Université de Strasbourg*   
*Réseaux locaux Licence 3 \- UFR Mathématique \-*   
*Informatique / Printemps 2023* 

**Réalisation projet**   
 **Codes correcteurs d’erreurs**

Réalisation: Clément Oberhauser / Marlind Tahiri

# Réponse aux questions

**Question 1:** Quel est le rendement du code décrit par la matrice G? Justifiez.

Pour calculer le rendement du code décrit par la matrice G, nous utilisons la formule R \= k/n (avec k la dimension de l’espace de message et n la longueur du mot de code. Dans ce cas, la matrice G est de taille k \= 8 bits et n \= 16 bits. On peut donc en conclure que le rendement de ce code est de 50% car R= 8/16 \= 0,5 soit 50%.

**Question 3:** Implémentez en C le code décrit par la matrice G. Plus précisément, vous…

Explication du code :  
Les bits de m sont analysés individuellement pour former un tableau de 8 éléments. Chaque élément du tableau correspond à un bit de m. Ensuite, le résultat est initialisé avec les 8 bits les plus significatifs de m (c'est-à-dire les bits de poids fort). Cela se fait en décalant les bits de m vers la droite de 8 positions. Enfin, les bits de data sont combinés pour former les 8 bits restants. Chaque bit est positionné à une certaine position dans result en fonction de sa position dans le tableau. Les opérations de combinaison sont effectuées en utilisant l'opération XOR (ou exclusif) sur les bits correspondants. Une fois que toutes ces opérations sont réalisées, on obtient le mot encodé.

**Question 4.2.** Écrivez une fonction uint8\_t dist\_code\_G() qui vérifie que la distance de Hamming du code représenté par G est égale à 4\. Expliquez votre algorithme.

Le but de cet algorithme est de calculer la distance minimale entre toutes les paires de positions.  
La fonction utilise deux boucles for imbriquées pour itérer à travers toutes les paires de positions dans la matrice G. La première boucle parcourt les indices de ligne de 0 à 6, et la deuxième boucle parcourt les indices de ligne de la première boucle plus un jusqu'à 7\. Cela garantit que chaque paire de positions est comparée une seule fois sans répétition.  
À chaque itération des boucles, la fonction compare les valeurs des distances pour les positions actuelles dans la matrice G. Si la différence entre ces distances est inférieure à la valeur actuellement stockée dans la variable distance, la fonction met à jour la valeur de distance avec la nouvelle différence. Ainsi, à la fin des boucles, distance contient la plus petite distance trouvée entre toutes les paires de positions.  
Si elle est égale à 4 c’est que c’est un code de Hamming de distance 4\.

**Question 4.3**. Sachant la distance, déduisez combien d’erreur(s) ce code peut détecter/corriger. Est-il pertinent d’avoir un code avec une distance paire ?

Pour un code de distance d, il est capable de détecter et corriger jusqu'à (d-1)/2 erreurs. Dans le cas de ce code G, avec une distance de 4, il peut détecter et corriger jusqu'à (4-1)/2 \= 1 erreur.  
Il est généralement préférable d'avoir une distance impaire pour les codes correcteurs d'erreurs, car cela garantit qu'il existe une distance minimale de 3 entre deux mots de code distincts. Cela permet de détecter au moins une erreur dans les mots de code et de corriger jusqu'à (d-1)/2 erreurs. Avec une distance paire, il peut y avoir des configurations où deux erreurs coïncident avec des bits différents et la détection ne fonctionnera pas correctement.

# Polynôme générateur

 Registre à décalage implémentant P(X) \= X8 \+ X7 \+ X5 \+ X4 \+ X3 \+ 1 :

![][image1]  
**Question 6:** Implémentez une fonction uint8\_t mod\_poly(uint16\_t m)...

 À chaque itération, la fonction vérifie si le bit en cours de traitement est égal à 1\. Si c'est le cas, cela indique que le terme correspondant du polynôme doit être pris en compte pour la division. Pour cela, la fonction effectue une opération de ou exclusif (XOR) entre \`reste\` et le polynôme décalé vers la gauche en fonction de la position du bit actuel dans \`reste\`. Cette opération de XOR est utilisée pour simuler la soustraction de termes polynomiaux.  
Après avoir effectué cette opération de XOR, le résultat est stocké dans la variable \`reste\`. On fait cela jusqu'à ce que tous les bits significatifs de \`reste\` soient traités.  
Enfin, la fonction retourne le résultat final contenu dans reste, qui correspond au reste de la division du mot m par le polynôme. Ce reste est utilisé pour détecter les erreurs dans le mot encodé.

**Question 8\.** Le résultat d’un mod\_poly du message erroné, est la même que la sortie de mod\_poly du mot ayant qu' un seul  bit avec l'erreur, et le reste étant à zéro. 

**Question 10:** Implémentez du décodage par syndrome en codant la fonction unsigned uint8\_t correct(uint16\_t m)...

La fonction prend en entrée un mot encodé \`m\` et commence par calculer le syndrome du mot en utilisant la fonction mod\_poly(). Le syndrome est obtenu en effectuant une division du mot par le polynôme prédéfini. Le syndrome résultant représente les erreurs potentielles présentes dans le mot.  
La fonction itère sur un tableau prédéfini de syndromes, syndromes\[\], qui contient les valeurs des syndromes correspondant à différentes configurations d'erreurs. À chaque itération, la fonction compare le syndrome calculé avec les syndromes du tableau pour trouver une correspondance.  
Lorsqu'une correspondance est trouvée, cela signifie que le syndrome correspond à une configuration d'erreur spécifique qui peut être corrigée. Dans ce cas, la fonction effectue une opération de correction en utilisant la fonction chg\_nth\_bit() pour inverser le bit correspondant dans le mot m. Cela permet de corriger l'erreur détectée.  
La fonction chg\_nth\_bit() effectue une opération de ou exclusif (XOR) entre le mot m et un masque qui a uniquement le bit à inverser positionné à Cette opération modifie uniquement le bit spécifié tout en laissant les autres bits inchangés.  
Une fois la correction effectuée, la fonction retourne le résultat de la correction, qui représente le bit corrigé du mot m.

**Question 11\.** Étudiez à présent les syndromes obtenus lorsque l’on considère 2 erreurs sur le mot. Répondez (en justifiant) aux questions suivantes :

1) Lorsque deux erreurs surviennent sur le mot, le syndrome à 2 bits est effectivement le résultat d'un XOR entre les syndromes correspondants aux erreurs individuelles. Cela est dû au fait que l'opération XOR est additive, ce qui signifie que l'erreur combinée produit un syndrome qui est la combinaison des syndromes individuels. Ainsi, il existe une correspondance unique entre les syndromes à 2 bits et les vecteurs d'erreur de 2 bits.  
     
2) Dans certains cas, il est possible de faire du décodage par syndrome correct lorsque deux erreurs surviennent sur le médium. Si les deux erreurs se trouvent à des positions différentes et que les syndromes correspondants sont distincts, le décodage par syndrome peut identifier les positions erronées et les corriger. Cependant, si les deux erreurs se trouvent à des positions similaires ou si les syndromes correspondants sont identiques, le décodage par syndrome peut ne pas être en mesure de détecter les erreurs ou de les corriger de manière fiable. Dans ces cas, des stratégies de décodage plus avancées seraient nécessaires pour assurer la correction des erreurs.  
     
3) Le code n'est pas parfait, car il ne peut pas corriger toutes les erreurs possibles. Le code est conçu pour détecter et corriger des configurations spécifiques d'erreurs, mais il n'est pas capable de détecter ou de corriger toutes les erreurs. Un code parfait serait en mesure de détecter et de corriger toutes les erreurs possibles sans échec.

**Question 12:** Nous allons néanmoins implémenter du décodage par syndrome supportant jusqu’à 2 erreurs. Plus précisément, vous implémenterez une fonction unsigned char correct2errors(uint16\_t m):

La fonction prend en entrée le mot encodé \`m\` et commence par calculer le syndrome du mot en utilisant la fonction mod\_poly(), de manière similaire à la fonction correct(). Le syndrome est obtenu en effectuant une division du mot par le polynôme prédéfini.  
Après, la fonction itère sur deux boucles l’une dans l’autre pour comparer toutes les paires possibles de syndromes pour trouver des correspondances. La première boucle itère sur les indices i allant de 0 à 7, alors que la deuxième boucle itère sur les indices j allant de i \+ 1 à 7\.  
À chaque itération, la fonction vérifie si le syndrome calculé correspond à la combinaison XOR des syndromes syndromes\[i\] et syndromes\[j\]. Si une correspondance est trouvée, ça veut dire qu’il y a deux erreurs.

# Conclusion

Dans la réalisation du projet sur les codes correcteurs d'erreurs, nous n'avons pas réussi à terminer la dernière question et la correction n’est que partielle. Avec plus de temps et d'efforts, il aurait été possible d'améliorer la correction du code.  
Ce projet a permis d'approfondir nos connaissances sur les codes correcteurs d'erreurs et leurs applications pratiques.  


[image1]: <data:image/png;base64,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>