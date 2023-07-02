import java.io.File
import kotlin.math.abs

object Day03 {
    private val inputFile = File("src\\main\\resources\\puzzle_input_03")
    private val inputData = inputFile.readLines()
    private const val gridSize =  30000
    private const val startRow = gridSize / 2
    private const val startCol = gridSize / 2

    fun solvePartOne(): Int{

        val matrix = Array(gridSize) { IntArray(gridSize) }

        var closestIntersection = Int.MAX_VALUE

        for (line in inputData)
        {
            var currentRow = startRow
            var currentCol = startCol
            val lineSteps = mutableSetOf<String>()

            val commands = line.split(",")
            for (command in commands){
                val dist = command.slice(1 until command.length)

                for (step in 0 until dist.toInt()){

                    when(command.first()){
                        'D' -> currentRow++
                        'U' -> currentRow--
                        'R' -> currentCol++
                        'L' -> currentCol--
                    }

                    if ((currentRow.toString() + currentCol.toString()) !in lineSteps){
                        matrix[currentRow][currentCol] += 1
                        lineSteps.add(currentRow.toString() + currentCol.toString())
                    }
                }
            }
        }

        for ((rowIndex, row) in matrix.withIndex()){
            for ((colIndex, col) in row.withIndex()){
                if (col >= 2) {
                    val absX = abs((rowIndex - startRow))
                    val absY = abs((colIndex - startCol))

                    closestIntersection = minOf(absX + absY, closestIntersection)
                }
            }
        }
        return closestIntersection
    }

    fun solvePartTwo(): Int? {

        // Draw first line
        val matrix1 = Array(gridSize) { IntArray(gridSize) }
        var currentRow = startRow
        var currentCol = startCol

        var commands = inputData[0].split(",")
        for (command in commands) {
            val dist = command.slice(1 until command.length)

            for (step in 0 until dist.toInt()) {

                when (command.first()) {
                    'D' -> currentRow++
                    'U' -> currentRow--
                    'R' -> currentCol++
                    'L' -> currentCol--
                }
                matrix1[currentRow][currentCol] = maxOf(matrix1[currentRow][currentCol], 1)
            }
        }
        // Check when second cross and keep track of steps
        currentRow = startRow
        currentCol = startCol
        var currentSteps = 0
        val line2Steps = mutableSetOf<String>()
        val crossLine2 = mutableMapOf<String, Int>()

        commands = inputData[1].split(",")
        for (command in commands) {
            val dist = command.slice(1 until command.length)

            for (step in 0 until dist.toInt()) {

                when (command.first()) {
                    'D' -> currentRow++
                    'U' -> currentRow--
                    'R' -> currentCol++
                    'L' -> currentCol--
                }
                if ((currentRow.toString() + currentCol.toString()) !in line2Steps){
                    matrix1[currentRow][currentCol] += 1
                    line2Steps.add(currentRow.toString() + currentCol.toString())
                }
                currentSteps++
                if (matrix1[currentRow][currentCol] == 2) {
                    crossLine2[currentRow.toString() + currentCol.toString()] = currentSteps
                }


            }
        }
        // Draw Second line
        val matrix2 = Array(gridSize) { IntArray(gridSize) }
        currentRow = startRow
        currentCol = startCol
        val line1Steps = mutableSetOf<String>()
        val crossLine1 = mutableMapOf<String, Int>()

        commands = inputData[1].split(",")
        for (command in commands) {
            val dist = command.slice(1 until command.length)

            for (step in 0 until dist.toInt()) {

                when (command.first()) {
                    'D' -> currentRow++
                    'U' -> currentRow--
                    'R' -> currentCol++
                    'L' -> currentCol--
                }
                matrix2[currentRow][currentCol] = maxOf(matrix2[currentRow][currentCol], 1)
            }
        }
        // Check when second cross and keep track of steps
        currentRow = startRow
        currentCol = startCol
        currentSteps = 0

        commands = inputData[0].split(",")
        for (command in commands) {
            val dist = command.slice(1 until command.length)

            for (step in 0 until dist.toInt()) {

                when (command.first()) {
                    'D' -> currentRow++
                    'U' -> currentRow--
                    'R' -> currentCol++
                    'L' -> currentCol--
                }
                if ((currentRow.toString() + currentCol.toString()) !in line1Steps){
                    matrix2[currentRow][currentCol] += 1
                    line1Steps.add(currentRow.toString() + currentCol.toString())
                }
                currentSteps++
                if (matrix2[currentRow][currentCol] == 2) {
                    crossLine1[currentRow.toString() + currentCol.toString()] = currentSteps
                }

            }
        }

        // Zip both map with key as grouping, add their value and return the minimum
        return crossLine1.keys.mapNotNull { key ->
            crossLine2[key]?.let { crossLine2Value ->
                crossLine1[key]?.plus(crossLine2Value)
            }
        }.minOrNull()
    }
}


