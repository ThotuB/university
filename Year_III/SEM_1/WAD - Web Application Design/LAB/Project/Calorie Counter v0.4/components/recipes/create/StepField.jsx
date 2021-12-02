import FormCard from "./FormCard"
import FormSection from "./FormSection"
import { Plus } from '../../svg/Heroicons'
import { useState } from "react"
import StepList from "./StepList"

function RecipeSteps() {
    const [step, setStep] = useState('')
    const [steps, setSteps] = useState([])

    const addStep = (step) => {
        if ( step === '' ) return
        setSteps([...steps, {content: step}])
        setStep('')
    }

    const removeStep = (index) => {
        setSteps(steps.filter((step, i) => i !== index))
    }

    return (
        <FormCard name="Steps" description="Make a recipe step-by-step">
            <FormSection>
                Add Step
                <div className="flex gap-1 rounded-xl border-4 border-purple-300 bg-purple-300">
                    <button className="px-3 pl-4 rounded-l-md text-white
                                    hover:ring hover:ring-gray-800 hover:bg-gray-800"
                            onClick={() => addStep(step)}>
                        <Plus/>
                    </button>
                    <input
                        className="w-full rounded-r-md py-1 px-2 outline-none 
                                    focus:ring focus:ring-purple-500"
                        placeholder="Step"
                        value={step}
                        onChange={(e) => setStep(e.target.value)}/>
                </div>
                <StepList steps={steps} removeStep={removeStep}/>
            </FormSection>
        </FormCard>
    )
}

export default RecipeSteps