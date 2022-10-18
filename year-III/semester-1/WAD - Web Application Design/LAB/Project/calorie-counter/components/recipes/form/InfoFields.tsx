import FormCard from "./FormCard";
import FormSection from "./FormSection";
import { useState } from 'react';
import TextField from "components/common/TextField";
import TextArea from "components/common/TextArea";
import ImageField from "components/common/ImageField";
import { IRecipeInfo } from "types/recipe";

interface RecipeInfoProps {
    recipeInfo?: IRecipeInfo
    onSave: (info: IRecipeInfo) => void;
}

const defaultRecipeInfo = {
    name: "",
    description: "",
    image: ""
}

function RecipeInfo({recipeInfo = defaultRecipeInfo, onSave}: RecipeInfoProps) {
    const [name, setName] = useState<string>(recipeInfo.name);
    const [description, setDescription] = useState<string>(recipeInfo.description);
    const [image, setImage] = useState<string>(recipeInfo.image);
    const [dummyImage, setDummyImage] = useState<File | null>();

    const handleSave = () => {
        onSave({
            name,
            description,
            image
        });
    }

    const isSaved = () => {
        return name === recipeInfo.name && description === recipeInfo.description && image === recipeInfo.image;
    }

    return (
        <FormCard name="Recipe Info" description="Enter the recipe information" saved={isSaved()} onSave={handleSave}>
            <FormSection label="Name" required>
                <div className="flex items-center gap-3">
                    <div className="w-4/5">
                        <TextField className="py-1 px-2 border-gray-300"
                            placeholder="Recipe"
                            maxLength={50}
                            value={name}
                            onChange={(e) => setName(e.target.value)}
                        />
                    </div>
                    <div className="font-mono font-semibold">
                        {name.length} / 50
                    </div>
                </div>
            </FormSection>
            <FormSection label="Description" description="Brief description of the recipe." required>
                <TextArea className="py-1 px-2 border-gray-300"
                    placeholder="Description"
                    value={description}
                    onChange={(e) => setDescription(e.target.value)}
                />
            </FormSection>
            <FormSection label="Cover Photo">
                <ImageField onImageChange={setDummyImage} />
                <div className="flex items-center gap-2 px-2 font-bold">
                    url:
                    <TextField className="py-0"
                        placeholder="https://..."
                        value={image}
                        onChange={(e) => setImage(e.target.value)}
                    />
                </div>
            </FormSection>
        </FormCard>
    )
}

export default RecipeInfo;