import { Doughnut } from 'react-chartjs-2';

interface MacroProps {
	carbs: number;
	fat: number;
	protein: number;
}

export default function MacroGraph({ carbs, fat, protein }: MacroProps) {
	const data = {
		labels: ['Carbs', 'Fat', 'Protein'],
		datasets: [
			{
				data: [carbs, fat, protein],
				backgroundColor: ['#57FF95', '#FFE98A', '#FF7871'],
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
				fontSize: 16,
				fontStyle: 'bold',
				fontColor: '#fff',
			},
		},
		cutout: '60%',
		borderColor: '#d8b4fe',
		backgroundColor: '#000',
		borderWidth: 10,
	};

	return <Doughnut data={data} options={options} />;
}
