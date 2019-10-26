#include "include/integration.h"
#include <stdio.h>

int majorVersion() {
    printf("Trying to get Version\n");
    return MAJ_VER;
}

int minorVersion() {
    return MIN_VER;
}
int revisionNum() {
    return REV_VER;
}

void swift_tissue_initializeDefaultTissue() {
    tissue_initializeDefaultTissue();
}

int swift_cells_connectDirected(int from, int to, double strength) {
    return cells_connectDirected(from, to, strength);
}

//  Cell Types
int swift_tissue_getCellType(int index) {
    return tissue_getCellType(index);
}
void swift_cellTypes_setBehaviourForCellType(int cellType, CellTypeBehaviour *behaviour) {
    cellTypeBehaviours[cellType] = *behaviour;
}

//  Network stimulation
void swift_cells_stimulate(int * targets, double * strengths, int count) {
    cells_stimulate(targets, strengths, count);
}