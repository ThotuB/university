import FormCard from "./FormCard"
import FormSection from "./FormField"
import { PlusIcon } from "@heroicons/react/outline"
import { ChangeEvent, useState } from "react"
import StepItem from "./StepItem"
import Button from "components/common/Button"
import TextField from "components/common/TextField"
import { Step } from "./Form"

interface RecipeStepsProps {
    onSave: (steps: Step[]) => void
}

export default function RecipeSteps({ onSave }: RecipeStepsProps) {
    const [step, setStep] = useState('')
    const [steps, setSteps] = useState<Step[]>([] as Step[])

    const handleSave = () => {
        onSave(steps)
    }

    const handleAdd = () => {
        if (!step) return
        setSteps([...steps, { step: step }])
        setStep('')
    }

    const handleDelete = (index: number) => {
        setSteps(steps.filter((_, i) => i !== index))
    }

    const changeStep = ({ target: { value } }: ChangeEvent<HTMLInputElement>) => {
        setStep(value)
    }

    return (
        <FormCard name="Steps" description="Make a recipe step-by-step" onSave={handleSave}>
            <FormSection
                label="Add Step"
            >
                <div className="flex gap-2">
                    <Button className="px-3 pl-4 bg-purple-300 hover:ring hover:ring-gray-800"
                        onClick={handleAdd}
                    >
                        <PlusIcon className="w-5" />
                    </Button>
                    <div className="bg-purple-300 w-full p-1 rounded-lg">
                        <TextField
                            className="py-1 h-full"
                            placeholder="Step"
                            value={step}
                            onChange={changeStep} />
                    </div>
                </div>
                <div className="flex flex-col gap-1">
                    {steps.map((step, index) => (
                        <StepItem key={index} step={step} id={index} onDelete={() => handleDelete(index)} />
                    ))}
                </div>
            </FormSection>
        </FormCard>
    )
}