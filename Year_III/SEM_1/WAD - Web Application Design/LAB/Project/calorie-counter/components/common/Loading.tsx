export default function Loading() {
    return (
        <div className="flex gap-12 justify-center py-6">
            <div className="h-3 w-3 rounded-full bg-red-300 animate-load-1" />
            <div className="h-3 w-3 rounded-full bg-red-300 animate-load-2" />
            <div className="h-3 w-3 rounded-full bg-red-300 animate-load-3" />
            <div className="h-3 w-3 rounded-full bg-red-300 animate-load-4" />
            <div className="h-3 w-3 rounded-full bg-red-300 animate-load-5" />
        </div>
    )
}