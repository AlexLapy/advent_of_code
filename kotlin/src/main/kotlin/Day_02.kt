import java.io.File

object Day02 {
    private val inputFile = File("src\\main\\resources\\puzzle_input_02")
    private val inputData = inputFile.readLines()



    fun solvePartOne(noun: Int = 12, verb: Int = 2): Int{
        val inputDataInt = inputData[0].split(",").map { it.toInt() }.toIntArray()
        inputDataInt[1] = noun
        inputDataInt[2] = verb

        var currPos = 0

        while (true){
            val opcode = inputDataInt[currPos]
            if (opcode == 99) return inputDataInt[0]
            val inputPos1 = inputDataInt[currPos + 1]
            val inputPos2 = inputDataInt[currPos + 2]
            val outputPos = inputDataInt[currPos + 3]

            when (opcode){
                1 -> inputDataInt[outputPos] = inputDataInt[inputPos1] + inputDataInt[inputPos2]
                2 -> inputDataInt[outputPos] = inputDataInt[inputPos1] * inputDataInt[inputPos2]
            }
            currPos += 4
        }
    }

    fun solvePartTwo(): Int {

        for (noun in 0..99){
            for (verb in 0..99){
                if (solvePartOne(noun, verb) == 19690720) return 100 * noun + verb
            }
        }
        return 0
    }
}