import { Doughnut } from "react-chartjs-2";

function MacroGraph(props) {
  const { carbs, fat, protein } = props;

  const data = {
    labels: ["Carbs", "Fat", "Protein"],
    datasets: [
      {
        data: [carbs, fat, protein],
        backgroundColor: ["#57FF95", "#FFE98A", "#FF7871"],
      },
    ],
  };
  const options = {
    plugins: {
      legend: {
        display: false,
      },
      labels: {
        render: 'value',
        arc: true,
        fontSize: 16,
        fontStyle: "bold",
        fontColor: "#fff",
      }
    },
    cutout: "60%",
    borderColor: "#c4b5fd",
    backgroundColor: "#000",
    borderWidth: 10,
  };

  return <Doughnut data={data} options={options} />;
}

export default MacroGraph;
