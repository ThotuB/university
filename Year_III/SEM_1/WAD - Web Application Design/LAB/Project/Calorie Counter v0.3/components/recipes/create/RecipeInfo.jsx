import FormCard from "./FormCard";
import FormSection from "./FormSection";
import { AddPhoto } from '../../svg/Icons';

function RecipeInfo() {
    return (
        <FormCard name="Recipe Info" description="Enter the recipe information">
            <FormSection>
                Recipe Name *
                <input
                    className="border w-3/5 rounded-md py-1 px-2 outline-none border-gray-300 
                                focus:ring focus:border-purple-300 focus:ring-purple-300"
                    placeholder="Burgir"
                />
            </FormSection>
            <FormSection>
                Description
                <textarea
                    className="border rounded-md py-1 px-2 outline-none border-gray-300 
                                focus:ring focus:border-purple-300 focus:ring-purple-300 w-full"
                    placeholder="Very delicious burgir"
                />
                Brief description of the recipe.
            </FormSection>
            <FormSection>
                Cover Photo
                <div className="text-sm border-2 border-dashed border-gray-300 rounded-md p-4 flex flex-col items-center">
                    <AddPhoto />
                    <div className="text-gray-700">
                            <label htmlFor="file-upload" className="cursor-pointer font-semibold text-purple-600 hover:text-purple-400 ">
                                    Upload a file
                                    <input id="file-upload" name="file-upload" type="file" className="sr-only" />
                            </label>
                            {" "}or drag and drop
                    </div>
                    <div className="text-gray-500">
                            PNG, JPG up to 5MB
                    </div>
                </div>
            </FormSection>
        </FormCard>
    )
}

export default RecipeInfo;