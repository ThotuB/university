interface InstructionProps {
    instructions: string[]
}

export default function Ingredients({ instructions }: InstructionProps) {
    console.log(instructions)

    return (
        <div className="text-lg flex flex-col gap-7">
            {instructions.map((instruction, index) => (
                <div key={index} className="flex gap-4">
                    <div className="text-2xl text-purple-400 font-black">
                        {index + 1}
                    </div>
                    <div className="w-px bg-purple-400" />
                    <div className="">
                        {instruction}
                    </div>
                </div>
            ))
            }
        </div>
    )
}