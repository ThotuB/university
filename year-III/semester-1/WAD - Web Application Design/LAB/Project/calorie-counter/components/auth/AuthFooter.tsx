interface AuthFooterProps {
    text: string;
    label: string;
    onClick: () => void;
}

export default function AuthFooter({ text, label, onClick }: AuthFooterProps) {
    return (
        <div className="mt-6 text-xs font-light text-center text-gray-400">
            {text}
            <button className="font-medium text-gray-700 hover:underline" onClick={() => onClick()}>
                {label}
            </button>
        </div>
    );
}
