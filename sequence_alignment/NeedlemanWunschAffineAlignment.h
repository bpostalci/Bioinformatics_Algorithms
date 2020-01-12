/**
 * @description   Needleman-Wunsch algorithm with affine gap scoring (Affine Global Alignment)
 * @author        Berat Postalcioglu - 21401769 
 **/

#pragma once

void needleman_wunsch_affine_align(char *s1, char *s2, char *title1, char *title2, int gapopen, int gapext);