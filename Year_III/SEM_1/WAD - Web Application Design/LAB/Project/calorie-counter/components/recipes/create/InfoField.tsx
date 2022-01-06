import { Info } from "./Form";
import FormCard from "./FormCard";
import FormSection from "./FormField";
import { AddPhoto } from 'components/common/svg/Icons';
import { useState } from 'react';
import TextField from "components/common/TextField";
import TextArea from "components/common/TextArea";

interface RecipeInfoProps {
    onSave: (info: Info) => void;
}

function RecipeInfo({ onSave }: RecipeInfoProps) {
    const [name, setName] = useState<string>('');
    const [description, setDescription] = useState<string>('');
    const [image, setImage] = useState<string>('');

    const handleSave = () => {
        onSave({
            name,
            description,
            image
        });
    }

    return (
        <FormCard name="Recipe Info" description="Enter the recipe information" onSave={handleSave}>
            <FormSection label="Name">
                <TextField className="w-3/5 py-1 px-2 border-gray-300"
                    placeholder="Recipe"
                    value={name}
                    onChange={(e) => setName(e.target.value)}
                />
            </FormSection>
            <FormSection label="Description"
                description="Brief description of the recipe."
            >
                <TextArea className="py-1 px-2 border-gray-300"
                    placeholder="Description"
                    value={description}
                    onChange={(e) => setDescription(e.target.value)}
                />
            </FormSection>
            <FormSection
                label="Cover Photo"
            >
                <div className="text-sm border-2 border-dashed border-gray-300 rounded-md p-4 flex flex-col items-center">
                    <AddPhoto />
                    <div className="text-gray-700">
                        <label className="font-semibold text-purple-600 hover:text-purple-400 ">
                            Upload a file
                            <input type="file" className="sr-only" />
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