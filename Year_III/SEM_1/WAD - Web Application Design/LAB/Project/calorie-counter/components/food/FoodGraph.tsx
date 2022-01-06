import MacroGraph from "components/common/MacroGraph";

interface FoodGraphProps {
    macros: {
        carbs: number;
        fat: number;
        protein: number;
    };
    calories: number;
}

function FoodGraph({ macros: {carbs, fat, protein}, calories }: FoodGraphProps) {
    return (
        <div className="w-1/5 bg-purple-300 relative flex justify-center items-center p-1">
            <div className="z-10 w-full">
                <MacroGraph carbs={carbs} protein={protein} fat={fat} />
            </div>
            <div className="absolute text-gray-800 font-bold font-mono text-4xl z-0">
                {calories}
            </div>
        </div>
    );
}

export default FoodGraph;
