export interface NutrientProps {
    label: string;
    quantity?: number | string;
    unit?: string;
}

export default function FoodNutrient({ label, quantity, unit }: NutrientProps) {
    return (
        <div className="flex w-full justify-between py-3 px-7 text-2xl font-bold">
            <div>
                {label}
            </div>
            <div className="flex flex-row-reverse w-52 gap-5">
                <div className="w-16">
                    {unit}
                </div>
                <div className="text-right">
                    {quantity}
                </div>
            </div>
        </div>
    )
}