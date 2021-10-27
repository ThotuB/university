import MacroGraph from "../common/MacroGraph";

function FoodGraph(props) {
  const { macros, calories } = props;
  const { carbs, protein, fat } = macros;

  return (
    <div className="w-1/5 bg-purple-300 relative flex justify-center items-center p-1">
      <div className="absolute text-gray-800 font-bold font-mono text-4xl">
        {calories}
      </div>
      <MacroGraph carbs={carbs} protein={protein} fat={fat} />
    </div>
  );
}

export default FoodGraph;
