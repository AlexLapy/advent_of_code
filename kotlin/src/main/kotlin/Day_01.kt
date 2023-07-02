import java.io.File

object Day01 {
    private val inputFile = File("src\\main\\resources\\puzzle_input_01")
    private val inputData = inputFile.readLines()

    fun solvePartOne() = inputData.sumOf { it.toInt().floorDiv(3) - 2 }

    fun solvePartTwo(): Int {
        var inputDataInt = inputData.map { it.toInt() }
        var sum2 = 0
        while (inputDataInt.isNotEmpty()){

            inputDataInt = inputDataInt.map { it.floorDiv(3) - 2 }.filter { it > 0 }
            sum2 += inputDataInt.sumOf { it }
        }
        return sum2
    }
}