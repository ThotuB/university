import FormCard from "./FormCard";
import FormSection from "./FormSection";
import { Plus } from '../../svg/Heroicons'

function RecipeSteps() {
    return (
        <FormCard name="Steps" description="Make a recipe step-by-step">
            <FormSection>
                Add Step
                <div className="flex gap-1 rounded-xl border-4 border-purple-300 bg-purple-300">
                    <button className="px-3 pl-4 rounded-l-md text-white
                                    hover:ring hover:ring-gray-800 hover:bg-gray-800">
                        <Plus/>
                    </button>
                    <input
                        className="w-full rounded-r-md py-1 px-2 outline-none 
                                    focus:ring focus:ring-purple-500"
                        placeholder="Burgir"
                    />
                </div>
            </FormSection>
        </FormCard>
    )
}

export default RecipeSteps;