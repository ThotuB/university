import { RecipeDto } from "types/recipe";
import Ingredients from "./Ingredients";
import Instructions from "./Instructions";

interface Props {
    recipe: RecipeDto;
}

export default function Recipe({ recipe: { id, name, description, image, ingredients, steps, user: { id: userId, name: userName, image: userImage } } }: Props) {
    console.log(image)

    return (
        <div className="w-full h-full bg-white rounded-3xl overflow-hidden flex flex-col gap-8 font-futura-light">
            <div className="relative">
                <div className="absolute -bottom-6 flex justify-center w-full text-5xl">
                    <div className="p-6 back backdrop-blur font-bold border border-gray-800">
                        {name}
                    </div>
                </div>
                {image ? 
                    <img src={image} className="w-full h-full object-cover" /> :
                    <div className="h-24 bg-red-300" />
                }
            </div>
            <div className="flex flex-col gap-8 px-10 py-4">
                <div className="flex flex-col gap-8">
                    <div className="bg-gray-800 w-full h-px" />
                    <div className="px-10 text-lg">
                        {description}
                    </div>
                    <div className="bg-gray-800 w-full h-px" />
                </div>
                <div className="flex gap-12">
                    <div className="w-3/12">
                        <div className="text-3xl flex flex-col gap-5">
                            INGREDIENTS
                            <Ingredients ingredients={ingredients} />
                            <div className="bg-gray-800 w-full h-px" />
                        </div>
                    </div>
                    <div className="w-9/12">
                        <div className="text-3xl flex flex-col gap-5">
                            COOKING INSTRUCTIONS
                            <Instructions instructions={steps} />
                        </div>
                    </div>
                </div>
            </div>
        </div>
    )
}