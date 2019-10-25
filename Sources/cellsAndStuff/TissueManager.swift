import cCellsAndStuff

public class TissueManager {

    
    public init() {
        
    }
    

    public func initializeDefaultTissue() {
        cCellsAndStuff.swift_tissue_initializeDefaultTissue()
    }

    public func connectCell(from: Int32, to: Int32, strength: Double) {
        let result = cCellsAndStuff.swift_cells_connectDirected(from, to, strength)
        if result != 0 {
            print("Failed to Connect cells - see log for details")
        }
    }

    public func cell(at index: Int32) -> Cell? {

        let cellTypeRaw = cCellsAndStuff.swift_tissue_getCellType(index)
        guard let cellType = DefaultCellTypes(rawValue: cellTypeRaw) else {
            return nil
        }

        return Cell(type: cellType)

    }

}