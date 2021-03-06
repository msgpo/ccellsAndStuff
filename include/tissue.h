#ifndef TISSUE_IN
#define TISSUE_IN

#define NUM_CELLS 100

static int chkTissueCreated();

/**
 * Initialize the system with a default tissue along with default behaviours/cell types
 */
void tissue_initializeDefaultTissue();
int * getTissue();

/**
 * Current state of the tissue in terms of what cells are lit up/stimulated
 */
typedef struct TissueState {

    int * outputIndices;
    double * outputStrengths;
    int outputCount;

} TissueState;

static TissueState * _getState(int reset) {
    static int initd = 0;

    static TissueState state;
    if(initd == 0 || reset == 1) {

        free(state.outputIndices);
        free(state.outputStrengths);

        state.outputCount = 0;
        state.outputIndices = malloc(sizeof(int));
        state.outputStrengths = malloc(sizeof(double));
        initd = 1;
    }
    

    return &state;
}

void tissue_state_reset() {
    _getState(1);
}

void tissue_initializeDefaultTissue() {
    getTissue();
    cellTypes_InitializeDefaultCellTypeBehaviours();
    cellTypes_initializeCellTypeColors();
}

TissueState * tissue_getState() {
    
    TissueState *currentState = _getState(0);

    TissueState *ret = malloc(sizeof(TissueState));
    ret->outputCount = currentState->outputCount;
    ret->outputIndices = malloc(sizeof(int) * ret->outputCount);
    ret->outputStrengths = malloc(sizeof(double) * ret->outputCount);

    int i;
    for(i=0; i<ret->outputCount; i++) {
        ret->outputIndices[i] = currentState->outputIndices[i];
        ret->outputStrengths[i] = currentState->outputStrengths[i];
    }
    
    #ifndef NDEBUG
    printf("TISSUE STATE:\n=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~\n");
    printf("Count = %d\n", ret->outputCount);
    
    for(i=0; i<ret->outputCount; i++) {
        printf("IDX:\t%d\t%f\n", ret->outputIndices[i], ret->outputStrengths[i]);
    }
    printf("=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~\n");
    #endif

    return ret;

}

static void (*onUpdateStateCallback)(TissueState * state);
static int updateCallbackRegistered = 0;
void tissue_registerStateUpdateListener(void (*onStateUpdate)(TissueState * state)) {
    onUpdateStateCallback = onStateUpdate;
    updateCallbackRegistered = 1;
}

void tissue_pushState() {
    if(updateCallbackRegistered) {
        onUpdateStateCallback(tissue_getState());
    }
}

void tissue_state_updateOutputToCell(int index, double strength) {
    
    TissueState * state = _getState(0);
    state->outputCount++;

    state->outputIndices = realloc(state->outputIndices, state->outputCount*sizeof(int));
    state->outputStrengths = realloc(state->outputStrengths, state->outputCount*sizeof(double));

    state->outputIndices[state->outputCount-1] = index;
    state->outputStrengths[state->outputCount-1] = strength;

    #ifdef TRACEDEBUG
    printf("Added output cell idx=%d, stren=%f\n", index, strength);
    #endif
}

void tissue_setCellType(int index, int cellType);
void tissue_setCellType(int index, int cellType) {
    if(index >= NUM_CELLS) {
        fprintf(stderr, "Cannot assign cell type to undefined index %d\n", index);
        return;
    }
    int * tissueRef = getTissue();
    *(tissueRef + index) = cellType;
}

int tissue_getCellType(int index);
int tissue_getCellType(int index) {
    if(index >= NUM_CELLS) {
        fprintf(stderr, "Cannot access cell at undefined index %d\n", index);
        return -1;
    }
    return getTissue()[index];
}

int tissue_getNumCells();
int tissue_getNumCells() {
    return NUM_CELLS;
}

/**
 * Execute the cell behaviours for all cells in this tissue.  See also
 * tissue_setBehaviourForCellType()
 */
void tissue_executeCellBehaviours();
void tissue_executeCellBehaviours() {
    int i;
    int cellType;
    for(i=0; i<NUM_CELLS; i++) {
        cellType = tissue_getCellType(i);
        if(cellTypes_existsBehaviourForCellType(cellType)) {
            cellTypes_behaviourFor(cellType) -> executeCellBehaviour(cellType, i);
        }
    }
}

static int chkTissueCreated() {
    static int created = 0;

    int ret = created;
    if(created == 0){
        created = 1;
    }

    return ret;
}

int * getTissue() {
   static int tissueData[NUM_CELLS];
   if(chkTissueCreated() == 0) {
       logD("Creating tissue...");
       int idx = 0;
       for(idx=0; idx < NUM_CELLS; idx++) {
           tissueData[idx] = CELL_TYPE_BASIC;
       }
   } else {
       #ifdef TRACEDEBUG
       logD("Tissue already created");
       #endif
   }

   return tissueData;

}

#endif