interface DividerProps {
    className?: string;
}

export default function Divider({ className }: DividerProps) {
    return (
        <hr className={`${className} border-gray-200 border-2 rounded-full`} />
    )
}